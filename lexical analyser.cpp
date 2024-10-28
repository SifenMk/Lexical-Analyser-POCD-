#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

enum class TokenType
{
  KEYWORD,
  IDENTIFIER,
  OPERATOR,
  LITERAL,
  PUNCTUATOR
};

struct Token
{
  string value;
  TokenType type;
};

class LexicalAnalyzer
{
public:
  LexicalAnalyzer(const string &input) : input_(input) {}
  void analyze()
  {
    stack<Token> tokenStack;
    string tokenValue;

    for (char c : input_)
    {
      if (isspace(c))
      {
        if (!tokenValue.empty())
        {
          tokenStack.push({tokenValue, getTokenType(tokenValue)});
          tokenValue.clear();
        }
      }
      else
      {
        tokenValue += c;
      }
    }

    if (!tokenValue.empty())
    {
      tokenStack.push({tokenValue, getTokenType(tokenValue)});
    }

    while (!tokenStack.empty())
    {
      Token token = tokenStack.top();
      tokenStack.pop();
      cout << "Token: " << token.value << ", Type: " << getTokenTypeString(token.type) << endl;
    }
  }

private:
  TokenType getTokenType(const string &tokenValue)
  {
    if (isKeyword(tokenValue))
      return TokenType::KEYWORD;
    if (isIdentifier(tokenValue))
      return TokenType::IDENTIFIER;
    if (isOperator(tokenValue))
      return TokenType::OPERATOR;
    if (isLiteral(tokenValue))
      return TokenType::LITERAL;
    if (isPunctuator(tokenValue))
      return TokenType::PUNCTUATOR;
    return TokenType::IDENTIFIER;
  }

  string getTokenTypeString(TokenType type)
  {
    switch (type)
    {
    case TokenType::KEYWORD:
      return "KEYWORD";
    case TokenType::IDENTIFIER:
      return "IDENTIFIER";
    case TokenType::OPERATOR:
      return "OPERATOR";
    case TokenType::LITERAL:
      return "LITERAL";
    case TokenType::PUNCTUATOR:
      return "PUNCTUATOR";
    default:
      return "UNKNOWN";
    }
  }

  bool isKeyword(const string &tokenValue)
  {
    unordered_map<string, bool> keywords = {
        {"int", true},
        {"char", true},
        {"float", true},
        {"double", true}};
    return keywords.find(tokenValue) != keywords.end();
  }

  bool isIdentifier(const string &tokenValue)
  {
    return isalpha(tokenValue[0]);
  }

  bool isOperator(const string &tokenValue)
  {
    unordered_map<string, bool> operators = {
        {"=", true},
        {"+", true},
        {"-", true},
        {"*", true},
        {"/", true}};
    return operators.find(tokenValue) != operators.end();
  }

  bool isLiteral(const string &tokenValue)
  {
    return isdigit(tokenValue[0]);
  }
bool isPunctuator(const string &tokenValue)
  {
    unordered_map<string, bool> punctuators = {
        {",", true},
        {";", true},
        {"(", true},
        {")", true},
        {"{", true},
        {"}", true},
        {"[", true},
        {"]", true}};
    return punctuators.find(tokenValue) != punctuators.end();
  }

  string input_;
};

int main()
{
  string input = "int age = 25;";
  LexicalAnalyzer analyzer(input);
  analyzer.analyze();
  return 0;
}