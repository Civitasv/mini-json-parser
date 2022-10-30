# Mini JSON Parser

This library follows the Json Spec described at <http://json.org>.

## Implementation Steps

1. ʵ�� Scanner�����ڴʷ�������ɨ�� json �ַ�������ȡ TokenType��
2. ʵ�� Parser�������﷨���������� json spec �������� json �﷨��ʽ���� Scanner ���ɵ� Tokens ���н������Ӷ�����Ϊ C++ �е� map �� vector��

�ڶ��׶κ������ڳ����﷨����AST�������ɡ��������Ϊ AST �Ƕ� Tokens ���������һ�������ʽ��

�������ڱ���ʱ������Ҳ�ǰ����������裬���ȴʷ�����������ͬ�� json ���������ǣ����﷨�����׶Σ����ǽ�Դ����ת��ΪĿ�����Եĸ�ʽ��

## Example

```c++
using namespace civitasv::json;
auto source = R"(
{
    "glossary" : {
    "test": true,
    "hello": null,
    "hello2": "miao\nmiao"
    }
}
)";

auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

Scanner scanner(source);
Parser parser(scanner);

JsonElement* res = parser.Parse();
JsonObject* obj = res->AsObject();

obj->insert({"tes", new JsonElement(20.0f)});

std::cout << res->dumps()  << '\n';

delete res;
```

���������

```txt
{"glossary": {"hello": null, "hello2": "miao\nmiao", "test": true}, "tes": 20}
```
