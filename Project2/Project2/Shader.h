#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <string>
#include <vector>

#define BuferLengLog 1024
#define TextLogErrorCompileShader "Ошибка компиляции шейдера, расположеного по пути"
#define TextErrorCompileProgramShaders "Не удалось скомпилировать программу шейдера"
#define TextCompileShadersError "Произошла ошибка компиляции одного из шейдеров"
#define TextExeptionError "Возникла ошибка код ошибки:"

class Shader
{
public:
	uint32_t ShaderId_GL;
	bool StateBild = false;

	Shader(const char* VertexPath, const char* FragmentPath)
	{
		uint32_t shaderVertex = glCreateShader(GL_VERTEX_SHADER);
		uint32_t shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
		StateBild = (shaderLoad(VertexPath, shaderVertex) && shaderLoad(FragmentPath, shaderFragment));
		if (!StateBild)
			std::cout << TextCompileShadersError << std::endl;
		ShaderId_GL = glCreateProgram();
		glAttachShader(ShaderId_GL, shaderVertex);
		glAttachShader(ShaderId_GL, shaderFragment);
		glLinkProgram(ShaderId_GL);
		StateBild = chackCompile(ShaderId_GL, ProgramType, NULL) && StateBild;
		glDeleteShader(shaderVertex);
		glDeleteShader(shaderFragment);
	}

private:
	enum typeCompileCheck
	{
		ShaaderType,
		ProgramType
	};
	/// <summary>
	/// Проверка успешности компиляции
	/// </summary>
	/// <param name="id">Индификатор обьекта (шейдер или программа)</param>
	/// <param name="type">Тип обьекта</param>
	/// <param name="filePatch">Доп параметр для шейдеров</param>
	/// <returns>успешность компиляции</returns>
	bool chackCompile(uint32_t id, typeCompileCheck type, const char* filePatch)
	{
		int idEror;
		if (type == ShaaderType)
			glGetShaderiv(id, GL_COMPILE_STATUS, &idEror);
		else
			glGetProgramiv(id, GL_COMPILE_STATUS, &idEror);
		if (!idEror)
		{
			char buferLog[BuferLengLog];
			if (type == ShaaderType)
				glGetShaderInfoLog(id, BuferLengLog, NULL, buferLog);
			else
				glGetProgramInfoLog(id, BuferLengLog, NULL, buferLog);
			using namespace std;
			if (type == ShaaderType)
				cout << TextLogErrorCompileShader << endl << "PATCH= " << filePatch << endl << buferLog << endl;
			else
				cout << TextErrorCompileProgramShaders << endl << buferLog << endl;
			return false;
		}
		return true;
	}
	/// <summary>
	/// Загрузка шейдера
	/// </summary>
	/// <param name="filePatch">Путь к шейдеру</param>
	/// <param name="shaderId">Индификатор СОЗДАННОГО шейдера</param>
	/// <returns>результат успешности компиляции</returns>
	bool shaderLoad(const char* filePatch, uint32_t& shaderId)
	{
		try
		{
			std::ifstream is(filePatch);
			std::vector<const char*> lines;
			std::vector<int32_t> lengths;
			std::string* strBuff;
			while (!is.eof())
			{
				strBuff = new std::string;
				std::getline(is, *strBuff);
				strBuff->append("\n");
				lengths.push_back(strBuff->size());
				lines.push_back((*strBuff).data());
			}
			glShaderSource(shaderId, lines.size(), lines.data(), lengths.data());
			glCompileShader(shaderId);
			return chackCompile(shaderId, ShaaderType, filePatch);
		}
		catch (int CodeError)
		{
			std::cout << TextExeptionError << CodeError << std::endl;
			return false;
		}
	}
};