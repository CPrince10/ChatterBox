# CMakeList.txt: chatroom-service 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

#引入第三方库的头文件库
include_directories("./include")

# 链接库路径
link_directories (${PROJECT_SOURCE_DIR}/chatroom-service/lib-sql)
link_directories (${PROJECT_SOURCE_DIR}/chatroom-service/lib-hv)

# 将源代码添加到此项目的可执行文件。
add_executable (chatroom-service   "main.cpp" "include/api.cpp"   "init.cpp" "controller/controller.cpp" "service/service.cpp" "dao/message.cpp" "dao/client.cpp" "dao/user.cpp")

# 链接库
target_link_libraries (chatroom-service mysqlcppconn pthread OpenSSL::SSL hv)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chatroom-service PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。		
