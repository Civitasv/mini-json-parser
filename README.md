# Mini JSON Parser

This library follows the Json Spec described at <http://json.org>.

## Implementation Steps

1. 实现 Scanner，用于词法分析，扫描 json 字符串，获取 TokenType。
2. 实现 Parser，用于语法分析，根据 json spec 中描述的 json 语法格式，对 Scanner 生成的 Tokens 进行解析，从而解析为 C++ 中的 map 和 vector。

第二阶段很类似于抽象语法树（AST）的生成。可以理解为 AST 是对 Tokens 分析后的另一种输出格式。

## Example

```c++
using namespace civitasv::json;
auto source =
    "{"
    "\"glossary\" : {"
    "  \"test\": true,"
    "  \"hello\": 10.2,"
    "  \"hello2\": \"miaomiao\""
    "}"
    "}";

auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

Scanner scanner(source);
Parser parser(scanner);

JsonElement* res = parser.Parse();
JsonObject* object = res->AsObject();

std::cout << *res << '\n';

delete res;
```

将会输出：

```txt
{
"glossary": {
"hello": 10.2,
"hello2": "miaomiao",
"test": true
}

}
```
