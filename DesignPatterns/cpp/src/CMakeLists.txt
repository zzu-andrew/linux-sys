
# 针对cmake版本的要求
# cmake version 3.18.3
cmake_minimum_required(VERSION 3.5)

project(cppDesignPatterns)

add_definitions("-Wall -g")

# 开闭原则
add_executable(open_close_principle open_close_principle.cpp)
# 依赖颠倒原则
add_executable(reverse_dependencies reverse_dependencies.cpp)
# 懒汉式单例模式
add_executable(sluggard_singleton sluggard_singleton.cpp)
# 饿汉式单例模式
add_executable(hungry_singleton hungry_singleton.cpp)
# 简单工厂模式
add_executable(simple_factory simple_factory.cpp)
# 工厂模式
add_executable(factory_mode factory_mode.cpp)
# 抽象工厂模式
add_executable(abstract_factory abstract_factory.cpp)
# 建造者模式问题抛出 -- 为什么需要建造者模式
add_executable(builder_pattern_question builder_pattern_question.cpp)
# 建造者模式
add_executable(builder_pattern builder_pattern.cpp)
# 代理者模式
add_executable(proxy_pattern proxy_pattern.cpp)
# 修饰者模式
add_executable(decorator_pattern decorator_pattern.cpp)
# 适配器模式
add_executable(adapter_pattern adapter_pattern.cpp)
# 桥接模式
add_executable(bridge_pattern bridge_pattern.cpp)
# 组合模式
add_executable(composite_pattern composite_pattern.cpp)
# 外观模式
add_executable(facade_pattern facade_pattern.cpp)
# 享元模式
add_executable(flyweight_pattern flyweight_pattern.cpp)
# 模板模式
add_executable(template_pattern template_pattern.cpp)
# 命令模式
add_executable(command_pattern command_pattern.cpp)
# 责任链模式
add_executable(cor_pattern cor_pattern.cpp)
# 策略模式
add_executable(strategy_pattern strategy_pattern.cpp)
# 中介者模式
add_executable(mediator_pattern mediator_pattern.cpp)
# 观察者模式
add_executable(observer_pattern observer_pattern.cpp)
# 备忘录模式
add_executable(memento_pattern memento_pattern.cpp)
# 备忘录模式
add_executable(visitor_pattern visitor_pattern.cpp)
# 状态模式
add_executable(state_pattern state_pattern.cpp)
# 解释模式
add_executable(interpreter_pattern interpreter_pattern.cpp)
# 迭代器模式
add_executable(iterator_pattern iterator_pattern.cpp)

