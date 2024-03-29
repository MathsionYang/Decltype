std::unique_ptr是C++11标准引入的智能指针，其核心思想是独占所有权（exclusive ownership）和资源管理的责任。

核心思想可以总结为以下几点：
独占所有权：std::unique_ptr独占所管理的指针资源，同一时间只能有一个std::unique_ptr拥有该资源。当std::unique_ptr被销毁或转移所有权时，它会自动释放所管理的资源，确保资源在适当的时候被正确释放，避免资源泄漏。
确保资源的释放：std::unique_ptr通过在析构函数中自动调用delete来释放所管理的资源。这意味着，无论是通过正常的控制流还是异常的控制流，只要std::unique_ptr被销毁，资源都会得到释放，避免了手动释放资源的繁琐和可能的遗漏。
禁止拷贝：std::unique_ptr禁止拷贝构造函数和拷贝赋值运算符的使用，以确保同一时间只有一个std::unique_ptr拥有资源的所有权。这样可以防止多个智能指针同时管理同一块资源，避免了资源的重复释放和悬挂指针的问题。
支持移动语义：std::unique_ptr支持移动构造函数和移动赋值运算符，允许资源的所有权从一个std::unique_ptr对象转移到另一个对象，避免了资源的不必要拷贝。
总的来说，std::unique_ptr的核心思想是通过独占所有权和自动释放资源的方式，提供了一种安全、高效的资源管理机制，减少了手动管理资源的复杂性和错误，并支持现代C++中的移动语义。
