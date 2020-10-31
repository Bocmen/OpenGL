#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <string>
#include <vector>

#define BuferLengLog 1024
#define TextLogErrorCompileShader "Ошибка компиляции шейдера, расположеного по пути"
#define TextErrorCompileProgramShaders "Не удалось скомпилировать программу шейдера"
#define TextCompileShadersError "Произошла ошибка компиляции одного из шейдеров"

class Shader
{
public:
	uint32_t ShaderId_GL;

	Shader(const char* VertexPath, const char* FragmentPath)
	{
		uint32_t shaderVertex = glCreateShader(GL_VERTEX_SHADER);
		uint32_t shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
		if (!(shaderLoad(VertexPath, shaderVertex) && shaderLoad(FragmentPath, shaderFragment)))
			std::cout << TextCompileShadersError << std::endl;
		ShaderId_GL = glCreateProgram();
		glAttachShader(ShaderId_GL, shaderVertex);
		glAttachShader(ShaderId_GL, shaderFragment);
		glLinkProgram(ShaderId_GL);
		chackCompile(ShaderId_GL, ProgramType, NULL);
		glDeleteShader(shaderVertex);
		glDeleteShader(shaderFragment);
	}

private:
	enum typeCompileCheck
	{
		ShaaderType,
		ProgramType
	};
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
	/// Чтение текстового файла целиком
	/// </summary>
	/// <param name="FilePatch">Путь к файлу</param>
	/// <returns></returns>
	const char** FileRead(const char* FilePatch)
	{
		std::ifstream is(FilePatch);
		std::vector<std::string> resul;
		std::string strBuff;
		const char* charsbuff;
		while (!is.eof())
		{
			std::getline(is, strBuff);
			resul.push_back(strBuff);
		}
		const char* res = resul[0].c_str();
		return &res;
	}
	bool shaderLoad(const char* filePatch, uint32_t& shaderId)
	{
		const char** ReadShader = FileRead(filePatch);
		//std::string textShader = FileRead(filePatch);
		//const char* textShaderChar_C = textShader.c_str();
		glShaderSource(shaderId, 6, ReadShader, NULL);
		glCompileShader(shaderId);
		return chackCompile(shaderId, ShaaderType, filePatch);
	}
};