# CFG.h

# Functions

## CFG
`CFG()`

- Return Value: `CFG`
    
  - Returns a new Context Free Grammar object.



## add_rule
`bool add_rule(std::string name, std::vector<std::string> products)`

- Parameters

  - `name`
   
    The name of the rule associated with the given products.

  - `products`
   
    A vector of string names that reference other rules or terminals.

- Return Value: `bool`
    
  - Returns `true` if the rule was added, or `false` if it was unable to be added because a rule or terminal with that name already exists.



## set_start_rule
`bool set_start_rule(std::string name)`

- Parameters

  - `name`
   
    The name of the rule that the CFG will start at when parsing input using `verify()`.

- Return Value: `bool`
    
  - Returns `true` if the rule was set, or `false` if it was unable to be set because a rule with that name does not exist.



## add_terminal
`bool add_terminal(std::string name, std::regex expr)`

- Parameters

  - `name`
   
    The name of the terminal.

  - `expr`
   
    A regex object that will be used to match when `verify()` is called on an input.

- Return Value: `bool`
    
  - Returns `true` if the terminal was added, or `false` if it was unable to be added because a terminal or rule with that name already exists.



## verify
`bool verify(std::vector<std::string> input)`

- Parameters

  - `input`
   
    A vector of strings that represent tokens.

- Return Value: `bool`
    
  - Returns `true` if the input matches the CFG object's grammar, or `false` if it does not match.



## add_rule
`std::string to_string() const`

- Return Value: `std::string`
    
  - Returns a string of the rules and terminals that represent the language that the `CFG` object would match with.




# Syntax Rules

###### I love syntax!!!!

Generally, this follows the same notation as a formal language theory textbook would when it comes to describing rules, so if you know those, this should be familiar to you. However, with that in mind, there are some syntax rules that are very important to be aware of when writing rules for matching. I wrote this with a vague idea of Chomsky Normal Form in mind, so if this doesn't work well for non-CNF grammars, I apologize. That said, I don't think that it actually matters whether or not a grammar is in CNF.

There are 2 special preset terminals that are added when a new `CFG` object is instatiated.

- `|`

  - This represents a case delimiter. The parser will read a rule from left to right and generate cases in that dorection as well. If a `|` is used, everythiing before that pipe will be considered a separate case from everything after it.

    e.g.) Say I have a rule that looks like `A | B C | none`. In this example, there are 3 cases: Case 1 is `A`, Case 2 is `B C` and Case 3 is `none`. The parser will try to match with Case 1 first and Case 3 last.

- `none`

  - This represents epsilon (`ε`), or the 'empty string' in a more formal notation. The way this is used interinally is that if a case is `none`, then it will automatically accept a match. Because of this, it is very important that, for any rule where the empty string is accepted, it is the **last** case in the rule. If it is not the last case, then every case after `none` will be unreachable because the parser will match with `none` and move on to the next rule or terminal in the previous rule.