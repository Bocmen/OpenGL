#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <locale.h>
#include <fstream>
#include <Shader.h>

uint32_t
X_Screen = 800,
Y_Screen = 600;

float_t vertices[] = {
		 0.5f,  0.5f, 0.0f,  // верхняя правая
		 0.5f, -0.5f, 0.0f,  // нижняя правая
		-0.5f,  0.5f, 0.0f   // верхняя левая
};
uint32_t indices[] = {  // помните, мы начинаем с 0!
		0, 1, 2,  // первый треугольник
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
		std::cout << "Не удалось зоздать окно" << std::endl;
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
	/// Шейдер работа
	Shader s = Shader("D:\\Изучение OpenGL\\Shader\\Project2\\Points.shader", "D:\\Изучение OpenGL\\Shader\\Project2\\Fragment.shader");
	int32_t shaderProgram = s.ShaderId_GL;

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после мы можем спокойно отвязать
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// помните: не отвязывайте EBO, пока VАО активен, поскольку связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// После этого вы можете отменить привязку VАО, чтобы другие вызовы VАО случайно не изменили этот VAO, но это редко происходит.
	// Изменение других значений VAO требует вызова glBindVertexArray в любом случае, поэтому мы обычно не снимаем привязку VAO (или VBO), когда это непосредственно не требуется.
	glBindVertexArray(0);

	

	while (!glfwWindowShouldClose(window))
	{
		// Обработка ввода
		// -----

		// Рендеринг
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// рисуем наш первый треугольник
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // поскольку у нас есть только один VАО, нет необходимости связывать его каждый раз, но мы сделаем это, чтобы все было немного более организованно
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0); // не нужно каждый раз его отвязывать  

		// glfw: обмен содержимым переднего и заднего буферов. Опрос событий Ввода\Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// опционально: освобождаем все ресурсы, как только они изжили своё назначение:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}