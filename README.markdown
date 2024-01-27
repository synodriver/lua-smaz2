# lua binding for [smaz2](https://github.com/antirez/smaz2)

### Usage

```lua
local smaz2 = require("smaz2")

local data = "hello lua"

encoded = smaz2.compress(data, 100)
print(encoded)
print(smaz2.decompress(encoded,100))
```