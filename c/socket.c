#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, client_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  // 创建socket文件描述符
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置socket选项，允许端口重用
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定端口
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 开始监听，最大连接队列为3
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    // 接受客户端连接
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address,
                            (socklen_t *)&addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // 处理客户端请求
    for (;;) {
      memset(buffer, 0, BUFFER_SIZE);

      // 读取客户端数据
      int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);

      if (bytes_read < 0) {
        perror("read error");
        break;
      } else if (bytes_read == 0) {
        // 客户端关闭连接
        break;
      }

      // 将数据回显给客户端
      int bytes_written = write(client_fd, buffer, bytes_read);
      if (bytes_written < 0) {
        perror("write error");
        break;
      }
    }

    // 关闭当前客户端连接
    close(client_fd);
  }

  close(server_fd);
  return 0;
}
