# CFG.h

## CFG
`CFG()`

- Return Value: `CFG`
    
    Returns a new Context Free Grammar object.



## add_rule
`bool add_rule(std::string name, std::vector<std::string> products)`

- Parameters

  - `name`
   
    The name of the rule associated with the given products.

  - `products`
   
    A vector of string names that reference other rules or terminals.

- Return Value: `bool`
    
    Returns `true` if the rule was added, or `false` if it was unable to be added because a rule or terminal with that name already exists.



## set_start_rule
`bool set_start_rule(std::string name)`

- Parameters

  - `name`
   
    The name of the rule that the CFG will start at when parsing input using `verify()`.

- Return Value: `bool`
    
    Returns `true` if the rule was set, or `false` if it was unable to be set because a rule with that name does not exist.



## add_terminal
`bool add_terminal(std::string name, std::regex expr)`

- Parameters

  - `name`
   
    The name of the terminal.

  - `expr`
   
    A regex object that will be used to match when `verify()` is called on an input.

- Return Value: `bool`
    
    Returns `true` if the terminal was added, or `false` if it was unable to be added because a terminal or rule with that name already exists.



## verify
`bool verify(std::vector<std::string> input)`

- Parameters

  - `input`
   
    A vector of strings that represent tokens.

- Return Value: `bool`
    
    Returns `true` if the input matches the CFG object's grammar, or `false` if it does not match.



## add_rule
`std::string to_string() const`

- Return Value: `std::string`
    
    Returns a string of the rules and terminals that represent the language that the `CFG` object would match with.
