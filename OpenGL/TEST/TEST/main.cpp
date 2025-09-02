#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

const char* vertexShaderSource = "#version 330 core\n"
								"layout (location = 0) in vec3 aPos;\n"
								"out vec4 vColor;\n"
								"void main()\n"
								"{\n"
								"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
								"vColor = vec4(0.0f,0.5f,0.1f,1.0f);"
								"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"uniform vec4 ourColor;"
									//"in vec4 vColor;"
									"void main()\n"
									"{\n"
									"vec4 color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
									"FragColor = ourColor;"
									"}\0";

int main()
{
	glfwInit();
	// 设置主要和次要版本 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.3);



	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Filed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to init GLAD" << endl;
		return -1;
	}

	// 设置视口
	glViewport(0, 0, 800, 600);

	// 注册窗口变化监视
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// 定义顶点数组
	float vertices[] = {
		 0.5f, 0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3 , // 第一个三角形
		1, 2, 3 , // 第二个三角形
	};

	// 生成 VBO 顶点缓冲对象
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 绑定 VAO 对象
	glBindVertexArray(VAO);

	// 绑定 VBO 缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 填充 VBO 数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定 EBO 对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 填充 EBO 数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// 创建顶点和片段着色器
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 附加着色器代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 检测是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); 
		cout << "ERROR:SHADER_VERTEX::COMPILE_FAILED \n" << infoLog << endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR:SHADER_FRAGMENT::COMPILE_FAILED \n" << infoLog << endl;
	}

	// 创建程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	
	// 将着色器附加到程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// 链接
	glLinkProgram(shaderProgram);
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR:SHADER_LINK_FAILED \n";
	}

	// 使用着色器程序
	glUseProgram(shaderProgram);

	// 删除着色器
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader);

	// 设置线框绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);  // no need to unbind it every time   

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		glUniform4f(ourColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	return 0;
}