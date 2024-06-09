# CFG.h

## add_rule
`bool add_rule(std::string name, std::vector<std::string> products)`

- Parameters

  1. `name`
        The name of the rule associated with the given products 

  1. `products`
        A vector of string names that reference other rules or terminals

- Return Value: `bool`
  - Returns `true` if the rule was added, or `false` if it was unable to be added because a rule with that name already exists
