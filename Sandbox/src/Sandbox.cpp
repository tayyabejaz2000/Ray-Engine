#include <Ray.h>

class SandBox : public Ray::Application
{
public:
	SandBox()
	{

	}
	~SandBox()
	{

	}
};

Ray::Application* Ray::CreateApplication()
{
	return new SandBox();
}