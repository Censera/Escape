#  Escape

Escape is a utility that escapes special symbols in a provided text.

Those symbols are:
- `\n`: Newline
- `\t`: Tab
- `\b`: Backspace
- `\r`: Carriage return
- `\f`: Form feed
- `"`: Double quote
- `'`: Single quote
- `\`: Backslash

## Usage

The content in file.txt is `John:	"Hello, I'm John."`

```bash
./build/escape tst/file.txt
```

Output: `John:\t\"Hello, I\'m John.\"\n

```bash
echo "John: \"Hello, I'm John.\"" | ./build/escape 
```

Output: `John: \"Hello, I\'m John.\"\n`
