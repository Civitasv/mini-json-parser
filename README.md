# Mini JSON Parser

This library follows the Json Spec described at <http://json.org>.

## Implementation Steps

1. ʵ�� Scanner�����ڴʷ�������ɨ�� json �ַ�������ȡ TokenType��
2. ʵ�� Parser�������﷨���������� json spec �������� json �﷨��ʽ���� Scanner ���ɵ� Tokens ���н������Ӷ�����Ϊ C++ �е� map �� vector��

�ڶ��׶κ������ڳ����﷨����AST�������ɡ��������Ϊ AST �Ƕ� Tokens ���������һ�������ʽ��

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

���������

```txt
{
"glossary": {
"hello": 10.2,
"hello2": "miaomiao",
"test": true
}

}
```
