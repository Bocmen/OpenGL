#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <locale.h>
#include <fstream>
#include <Shader.h>

uint32_t
X_Screen = 800,
Y_Screen = 600;

float_t Points[] =
{
		 0.5f,  0.5f, 0.0f,  // верхняя правая
		 0.5f, -0.5f, 0.0f,  // нижняя правая
		-0.5f, -0.5f, 0.0f,  // нижняя левая
		-0.5f,  0.5f, 0.0f   // верхняя левая
};

uint32_t Indices[] =
{
		0, 1, 3,  // первый треугольник
		1, 2, 3   // второй треугольник
};

int main()
{
	setlocale(LC_ALL, "Rus");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(X_Screen, Y_Screen, "Project 2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Не удалось создать окно" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Не удаётся связать OpenGL с Glad" << std::endl;
		return -1;
	}
	glfwSetWindowSizeLimits(window, 0, 0, X_Screen, Y_Screen);
	// Создание и компиляция шейдерной программы
	Shader shaderProgram = Shader("D:\\Изучение OpenGL\\Shader\\Project2\\Points.shader", "D:\\Изучение OpenGL\\Shader\\Project2\\Fragment.shader");
	if (!shaderProgram.StateBild)
	{
		glfwTerminate();
		return -1;
	}
	uint32_t VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); // Создаём обьект вершинного массива обязательно первым (поскольку он запоминает следующие действия?) (сначала связываем объект вершинного массива)
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO); // Конфигурируем вершинный атрибут(ы).

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Points), Points, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float_t), nullptr);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		// Обработка ввода
		// -----

		// Рендеринг
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// рисуем наш первый треугольник
		glUseProgram(shaderProgram.ShaderId_GL);
		glBindVertexArray(VAO); // поскольку у нас есть только один VАО, нет необходимости связывать его каждый раз, но мы сделаем это, чтобы все было немного более организованно
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0); // не нужно каждый раз его отвязывать  

		// glfw: обмен содержимым переднего и заднего буферов. Опрос событий Ввода\Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}