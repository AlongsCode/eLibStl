int 取屏幕高度();
int 取屏幕宽度();
void 延时(int 欲等待的时间);
/*关闭方式：1:#关机;2:#重启;3:#注销;4:#休眠5:#冬眠。注意在Windows95/98/ME下冬眠等同于休眠。*|**/
bool 关闭系统(int 关闭方式 = 1, bool 是否强制执行 = false);
bool 剪辑板可有文本();
//进程名称或窗口标题
bool 终止进程(std::wstring process_name_or_window_title);
//进程名称或窗口标题
bool 终止进程(std::string process_name_or_window_title);
//进程ID
bool 终止进程(unsigned int process_id);