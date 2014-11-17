#include "3DEngine.h"
#include "freeLook.h"
#include "freeMove.h"

#include "coreEngine.h"

class TestGame : public Game
{
public:
	TestGame() {}
	
	virtual void Init();
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
};

void TestGame::Init()
{
	GameObject* planeObject = new GameObject();
	GameObject* pointLightObject = new GameObject();
	GameObject* spotLightObject = new GameObject();
	GameObject* directionalLightObject = new GameObject();

	planeObject->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 0.5f, 4, 
																								 new Texture("bricks_normal.jpg"))));
	planeObject->GetTransform().SetPos(Vector3f(0, -1, 5));
	planeObject->GetTransform().SetScale(4.0f);
	
	pointLightObject->AddComponent(new PointLight(Vector3f(0,1,0),0.4f,Attenuation(0,0,1)));
	pointLightObject->GetTransform().SetPos(Vector3f(20,0,2));
	
	spotLightObject->AddComponent(new SpotLight(Vector3f(0,1,1),1.0f,Attenuation(0,0,0.1f), 0.7f));
	spotLightObject->GetTransform().SetRot(Quaternion(Vector3f(0,1,0), ToRadians(90.0f)));
	
	directionalLightObject->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.4f));
	
	GameObject* testMesh1 = new GameObject();
	
	testMesh1->AddComponent(new MeshRenderer(new Mesh("./res/models/cube.obj"), new Material(new Texture("bricks2.jpg"), 1, 8,
																								new Texture("bricks2_normal.jpg"),
																								new Texture("bricks2_disp.jpg"), 0.04f, -1.0f)));

	testMesh1->GetTransform().SetPos(Vector3f(0, 5, 0));
	testMesh1->GetTransform().SetRot(Quaternion(Vector3f(0,1,0), 0.4f));
	testMesh1->GetTransform().SetScale(5.0f);
	



	
	AddToScene(planeObject);
	AddToScene(pointLightObject);
	AddToScene(spotLightObject);
	AddToScene(directionalLightObject);
	AddToScene(testMesh1);
	pointLightObject->AddChild((new GameObject())
		->AddComponent(new Camera(Matrix4f().InitPerspective(ToRadians(70.0f), Window::GetAspect(), 0.5f, 1000.0f)))
		->AddComponent(new FreeLook())
		->AddComponent(new FreeMove()));
	
	directionalLightObject->GetTransform().SetRot(Quaternion(Vector3f(1,0,0), ToRadians(-45)));
}

int main()
{

	TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine");
	engine.Start();
	
	return 0;
}
