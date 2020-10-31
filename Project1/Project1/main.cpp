#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <locale.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, int q, int w, int e, int z);

int main()
{
	setlocale(LC_ALL, "Rus");
	glfwInit(); // Инцилизируем библеотеку (glad/glad.h работа с окнами)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // указывают версию клиентского API, с которой должен быть совместим созданный контекст. Точное поведение этих подсказок зависит от запрашиваемого клиентского API.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // указывают версию клиентского API, с которой должен быть совместим созданный контекст. Точное поведение этих подсказок зависит от запрашиваемого клиентского API.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // казывает, для какого профиля OpenGL следует создать контекст.
	GLFWwindow* window = glfwCreateWindow(800, 600, "Project 1", NULL, NULL); // Создание и запуск окна
	if (window == NULL)
	{
		std::cout << "Не удалось создать окно" << std::endl;
		glfwTerminate(); // очистить/удалить все выделенные для GLFW ресурсы.
		return -1;
	}
	glfwMakeContextCurrent(window); // мы сообщаем GLFW сделать контекст нашего окна основным контекстом в текущем потоке.
	glfwSetWindowSizeCallback(window, framebuffer_size_callback); // добавление события на измнение размера окна
	glfwSetKeyCallback(window, (GLFWkeyfun)processInput); // добавление обработчика нажатия на клавиши
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // glad: загрузка всех указателей на OpenGL-функции
	{
		std::cout << "Не удалось инцилизировать GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600); // нам нужно сообщить OpenGL размер видимой области окна
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window)) // Проверяется не закрыли ли окно
	{
		glClear(GL_COLOR_BUFFER_BIT); // Очищает цветовой буфер экрана (GL_COLOR_BUFFER_BIT — очистка буфера цвета; GL_DEPTH_BUFFER_BIT — очистка буфера глубины; GL_STENCIL_BUFFER_BIT — очистка буфера трафарета.)
		glfwSwapBuffers(window); // меняет местами цветовой буфер
		glfwPollEvents(); // следит за тем, инициируются ли какие-либо события (например, ввод с клавиатуры или перемещение мышки), обновляет состояние окна
	}
	glfwTerminate(); // очистить/удалить все выделенные для GLFW ресурсы.
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (scancode == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}