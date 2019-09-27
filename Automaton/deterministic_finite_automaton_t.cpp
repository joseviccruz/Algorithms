#include <bits/stdc++.h>

/** todo:
 * nfa;
 * unite;
 * intersect;
 * concatenate;
 * negate;
 * kleene_closure;
 * ...
**/

template <class W>
class deterministic_finite_automaton_t {
  using state_t = size_t;
  using symbol_t = W;

  std::vector<state_t> m_states;
  std::vector<symbol_t> m_alphabet;

  std::vector<std::pair<std::pair<state_t, symbol_t>, state_t>> m_transition_function;
  
  state_t m_initial_state;
  std::vector<state_t> m_accept_states;

  template <class T>
  void initialize(std::vector<T> &vect) const {
    std::sort(vect.begin(), vect.end());
    vect.resize(std::unique(vect.begin(), vect.end()) - vect.begin());
  }

  template <class T>
  size_t get_position(const std::vector<T> &vect, const T &value) const {
    auto ptr = std::lower_bound(vect.begin(), vect.end(), value);
    assert(ptr != vect.end());
    assert(*ptr == value);
    return std::distance(vect.begin(), ptr);
  }

  virtual void assert_transition_function() const {
    assert(m_transition_function.size() == m_states.size() * m_alphabet.size());
    std::vector<std::vector<size_t>> frequence(m_states.size(), std::vector<size_t>(m_alphabet.size()));
    for (const auto &args : m_transition_function) {
      const state_t &from = args.first.first;
      const symbol_t &symbol = args.first.second;
      const state_t &to = args.second;
      frequence[get_position(m_states, from)][get_position(m_alphabet, symbol)]++;
      get_position(m_states, to);
    }
    for (const std::vector<size_t> &vect : frequence) {
      for (const size_t &value : vect) {
        assert(value == 1);
      }
    }
  }

  virtual void assert_initial_state() const {
    get_position(m_states, m_initial_state);
  }

  virtual void assert_accept_states() const {
    for (const state_t &state : m_accept_states) {
      get_position(m_states, state);
    }
  }
    
public:
  deterministic_finite_automaton_t(const std::vector<state_t> &t_states,
                                   const std::vector<symbol_t> &t_alphabet,
                                   const std::vector<std::pair<std::pair<state_t, symbol_t>, state_t>> &t_transition_function,
                                   const state_t &t_initial_state,
                                   const std::vector<state_t> &t_accept_states)
  : m_states(t_states),
    m_alphabet(t_alphabet),
    m_transition_function(t_transition_function),
    m_initial_state(t_initial_state),
    m_accept_states(t_accept_states) {
      initialize(m_states);
      initialize(m_alphabet);
      initialize(m_transition_function);
      initialize(m_accept_states);

      assert_transition_function();
      assert_initial_state();
      assert_accept_states();
  }

  auto states() const -> const decltype (m_states)& {
    return m_states;
  }
  
  auto alphabet() const -> const decltype (m_alphabet)& {
    return m_alphabet;
  }
  
  auto transition_function() const -> const decltype (m_transition_function)& {
    return m_transition_function;
  }

  virtual std::vector<state_t> transition_arrows(const state_t &state, const symbol_t &symbol) const {
    auto ptr = std::lower_bound(m_transition_function.begin(), m_transition_function.end(), std::make_pair(std::make_pair(state, symbol), m_states.front()));
    
    std::vector<state_t> ret;
    while (ptr != m_transition_function.end()) {
      if (ptr->first != std::make_pair(state, symbol)) {
        break;
      }
      ret.push_back(ptr->second);
      ptr++;
    }
      
    assert(ret.size() == 1);
    return ret;
  }
  
  virtual bool run(const std::vector<symbol_t> &word) const {
    state_t current_state = m_initial_state;
    for (const symbol_t &symbol : word) {
      current_state = transition_arrows(current_state, symbol).front();
    }
    return std::lower_bound(m_accept_states.begin(), m_accept_states.end(), current_state) != m_accept_states.end();
  }
};

template <class W>
class nondeterministic_finite_automaton_t : public deterministic_finite_automaton_t<W> {
  // ...
};

template <class W>
using dfa_t = deterministic_finite_automaton_t<W>;

template <class W>
using nfa_t = nondeterministic_finite_automaton_t<W>;

auto main() -> decltype(42) {
  std::cout.setf(std::ios::boolalpha);
  const dfa_t<int> dfa({1, 2}, {0, 1}, {{{1, 0}, 1}, {{1, 1}, 2}, {{2, 0}, 1}, {{2, 1}, 2}}, 1, {1});
  for (auto [p, to] : dfa.transition_function()) {
    auto [from, symbol] = p;
    std::cout << '(' << from << ' ' << symbol << ' ' << to << ')' << '\n';
  }
  std::cout << dfa.run(std::vector<int>({1, 1, 1, 0, 1})) << '\n';
  return 0;
}
