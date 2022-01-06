/*
   author: cuiDarchan
   language: C++
   date: 2022.1.4
*/
#include <stdlib.h>
#include <iostream>
#include <string>

class Operation {
 public:
  virtual float getResult() = 0;
  inline float setNumA(const float& num) { numA = num; }
  inline float setNumB(const float& num) { numB = num; }
  float numA = 0;
  float numB = 0;
};

class OperationAdd : public Operation {
 public:
  float getResult() override {
    float result = 0;
    result = numA + numB;
    return result;
  }
};

class OperationSub : public Operation {
 public:
  float getResult() override {
    float result = 0;
    result = numA - numB;
    return result;
  }
};

class OperationMul : public Operation {
 public:
  float getResult() override {
    float result = 0;
    result = numA * numB;
    return result;
  }
};

class OperationDiv : public Operation {
 public:
  float getResult() override {
    float result = 0;
    if (numB != 0) {
      result = numA / numB;
    } else {
      std::cerr << "除数为0！" << std::endl;
    }
    return result;
  }
};

class OperationFactory {
 public:
  static Operation* createOperate(const char& operate) {
    Operation* op = nullptr;
    switch (operate) {
      case '+':
        op = new OperationAdd();
        break;
      case '-':
        op = new OperationSub();
        break;
      case '*':
        op = new OperationMul();
        break;
      case '/':
        op = new OperationDiv();
        break;
      default:
        std::cerr << "不支持的运算符!" << std::endl;
        break;
    }
    return op;
  }
};

int main(int argc, char** argv) {
  float numA = 0, numB = 0, result = 0;
  char strOpr = 0;

  std::cout << "请输入数字A：";
  std::cin >> numA;
  std::cout << "请输入数字B：";
  std::cin >> numB;
  std::cout << "请输入运算符号：";
  std::cin >> strOpr;

  Operation* opr = OperationFactory::createOperate(strOpr);
  if (opr == nullptr) {
    std::cerr << "不支持的运算符!" << std::endl;
  } else {
    opr->setNumA(numA);
    opr->setNumB(numB);
    result = opr->getResult();
    std::cout << "结果为：" << result << std::endl;
  }
  return 0;
}