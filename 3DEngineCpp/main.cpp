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

	planeObject->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks2.jpg"), 1, 8)));
	planeObject->GetTransform().SetPos(Vector3f(0, -1, 5));
	planeObject->GetTransform().SetScale(8.0f);
	
	pointLightObject->AddComponent(new PointLight(Vector3f(1,5,1),5.0f,Attenuation(5,0,1)));
	pointLightObject->GetTransform().SetPos(Vector3f(20,0,2));
	
	spotLightObject->AddComponent(new SpotLight(Vector3f(0,1,1),1.0f,Attenuation(0,0,0.1f), 0.7f));
	spotLightObject->GetTransform().SetRot(Quaternion(Vector3f(0,1,0), ToRadians(90.0f)));
	
	directionalLightObject->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.1f));
	
	GameObject* testMesh1 = new GameObject();
	GameObject* testMesh2 = new GameObject();
	GameObject* testMesh3 = new GameObject();
	GameObject* testMesh4 = new GameObject();
	GameObject* testMesh5 = new GameObject();
	GameObject* testMesh6 = new GameObject();
	GameObject* testMesh7 = new GameObject();
	
	testMesh1->AddComponent(new MeshRenderer(new Mesh("./res/models/cube.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh2->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh3->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh4->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh5->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh6->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	testMesh7->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("bricks.jpg"), 1, 8)));
	
	testMesh1->GetTransform().SetPos(Vector3f(0, 4, 0));
	testMesh1->GetTransform().SetRot(Quaternion(Vector3f(0,0,0), 0.4f));
	testMesh1->GetTransform().SetScale(5.0f);
	
	testMesh2->GetTransform().SetPos(Vector3f(0, 0, 25));
	testMesh2->GetTransform().SetRot(Quaternion(Vector3f(0, 1, 0), 0.4f));
	testMesh2->GetTransform().SetScale(1.0f);

	testMesh3->GetTransform().SetPos(Vector3f(0, 15, 25));
	testMesh3->GetTransform().SetRot(Quaternion(Vector3f(0, 1, 0), 0.4f));
	testMesh3->GetTransform().SetScale(1.0f);

	testMesh4->GetTransform().SetRot(Quaternion(Vector3f(0, 2, 0), 0.4f));
	testMesh5->GetTransform().SetRot(Quaternion(Vector3f(0, 3, 0), 0.4f));
	testMesh6->GetTransform().SetRot(Quaternion(Vector3f(0, 4, 0), 0.4f));
	testMesh7->GetTransform().SetRot(Quaternion(Vector3f(0, 5, 0), 0.4f));

	testMesh4->GetTransform().SetPos(Vector3f(0, 1, 25));
	testMesh5->GetTransform().SetPos(Vector3f(0, 2, 25));
	testMesh6->GetTransform().SetPos(Vector3f(0, 3, 25));
	testMesh7->GetTransform().SetPos(Vector3f(0, 4, 25));

	testMesh2->AddChild(testMesh4);
	testMesh2->AddChild(testMesh5);
	testMesh2->AddChild(testMesh6);
	testMesh2->AddChild(testMesh7);

	
	AddToScene(planeObject);
	AddToScene(pointLightObject);
	AddToScene(spotLightObject);
	AddToScene(directionalLightObject);
	AddToScene(testMesh1);
	AddToScene(testMesh2);
	AddToScene(testMesh3);
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
