/*
   author: cuiDarchan
   language: C++
   date: 2022.1.5
   program: 策略模式与简单工厂模式结合
*/
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

class CashSuper {
 public:
  virtual float acceptCash(const float money) = 0;
};

class CashNormal : public CashSuper {
 public:
  float acceptCash(const float money) override { return money; }
};

/*折扣*/
class CashRebate : public CashSuper {
 public:
  CashRebate(const float cash_rebate) { cash_rebate_ = cash_rebate; }
  float acceptCash(const float money) override { return money * cash_rebate_; }

 private:
  float cash_rebate_ = 0;
};

/*满减*/
class CashReturn : public CashSuper {
 public:
  CashReturn(const float cash_condition, const float cash_return) {
    cash_condition_ = cash_condition;
    cash_return_ = cash_return;
  }
  float acceptCash(const float money) override {
    if (money >= cash_condition_) {
      return money - std::floor(money / cash_condition_) * cash_return_;
    }
    return money;
  }

 private:
  float cash_condition_ = 0;
  float cash_return_ = 0;
};

class CashContext {
 public:
  /*构造函数里 添加switch策略*/
  CashContext(const char &cashType) {
    switch (cashType) {
      case 'A':
        cs_ = std::make_shared<CashNormal>();
        break;
      case 'B':
        cs_ = std::make_shared<CashRebate>(0.8);
        break;
      case 'C':
        cs_ = std::make_shared<CashReturn>(300, 100);
        break;
      default:
        std::cerr << "暂时没有该策略！" << std::endl;
        break;
    }
  }
  float getResult(const float money) {
    if (cs_) {
      cs_->acceptCash(money);
    } else {
      std::cerr << "保持原价！" << std::endl;
      return money;
    }
  }

 private:
  std::shared_ptr<CashSuper> cs_ = nullptr;
};

int main() {
  float price = 0, totalPrice = 0;
  int cnt = 0;
  char cashType = 0;

  std::cout << "请输入商品单价：";
  std::cin >> price;
  std::cout << "请输入商品数量：";
  std::cin >> cnt;

  totalPrice = price * cnt;
  std::cout << "请输入优惠策略 -- A（正常价格），B（8折），C（满300减100）:";
  std::cin >> cashType;

  CashContext cash_context(cashType);
  totalPrice = cash_context.getResult(totalPrice);
  std::cout << "商品总价为：" << totalPrice << std::endl;

  return 0;
}
