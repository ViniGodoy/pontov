/******************************************************************************
*
* COPYRIGHT Jonathan Ohara de Araujo ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Jonathan Ohara de Araujo
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distruição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <Ogre.h>
#include <OgreMeshManager.h>

#include <btBulletDynamicsCommon.h>

using namespace std;

#ifdef _DEBUG
#define PLUGINS_CFG "plugins_d.cfg"
#else
#define PLUGINS_CFG "plugins.cfg"
#endif

//Esta classe cuida de gerenciar todo funcionamento da fisica desse exemplo
//Ela mantém uma lista interna com todas formas físicas criadas e objetos de controle
// da Bullet
//Quando é destruída cuida de destruir todos objetos e liberar a memória
class PhysicsManager
{
	private:
		btDiscreteDynamicsWorld *mWorld;
		btCollisionDispatcher *mCollisionDispatcher;

		btDefaultCollisionConfiguration mCollisionConfig;		
		btDbvtBroadphase mBroadphase;
		btSequentialImpulseConstraintSolver mConstraintSolver;

		std::vector<btCollisionShape*> mCollisionShapes;

	public:
		PhysicsManager()
		{			
			mCollisionDispatcher = new btCollisionDispatcher(&mCollisionConfig);
	
			mWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, &mBroadphase, &mConstraintSolver, &mCollisionConfig);
		}

		~PhysicsManager()
		{
			for (int i=mWorld->getNumCollisionObjects()-1; i>=0 ;i--)
			{
				btCollisionObject* obj = mWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				mWorld->removeCollisionObject( obj );
				delete obj;
			}

			for(int i = 0, len = mCollisionShapes.size();i < len; ++i)
				delete mCollisionShapes[i];		

			delete mWorld;	
			delete mCollisionDispatcher;
		}

		void update(float ticks)
		{
			mWorld->stepSimulation(ticks);
		}

		btCollisionShape &createBoxShape(float x, float y, float z)
		{
			btCollisionShape *shape = new btBoxShape(btVector3(x / 2, y / 2, z / 2));
			mCollisionShapes.push_back(shape);

			return *shape;
		}

		btRigidBody &createBody(const btTransform &transform, float mass, btCollisionShape &shape)
		{
			bool isDynamic = (mass != 0.0f);

			btVector3 localInertia(0,0,0);

			if (isDynamic)
				shape.calculateLocalInertia(mass,localInertia);

			btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);

			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,&shape,localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);
			
			mWorld->addRigidBody(body);

			return *body;
		}
};

//Esta classe serve apenas de ponte entre corpos rigidos e scene nodes do Ogre
class SceneObject
{
	private:
		Ogre::SceneNode &mNode;
		btRigidBody &mRigidBody;

	public:
		SceneObject(Ogre::SceneNode &node, btRigidBody &body):
		  mNode(node),
		  mRigidBody(body)
		{
			//empty
		}
		
		void prepareToRender()
		{
			btTransform transform;

			mRigidBody.getMotionState()->getWorldTransform(transform);

			btQuaternion rotation(transform.getRotation());

			mNode.setOrientation(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ());

			const btVector3 &origin = transform.getOrigin();
			mNode.setPosition(origin.getX(), origin.getY(), origin.getZ());
		}
};


class Tutorial1 
{
	private:
		auto_ptr<Ogre::Root> mRoot;
		Ogre::Camera* mCamera;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mWindow;

		PhysicsManager mPhysics;

		std::vector<SceneObject *> mObjects;

	public:
		Tutorial1(void){}
		~Tutorial1(void)
		{			
			for(int i = 0, len = mObjects.size();i < len; ++i)
				delete mObjects[i];
		}

		bool initializeOgreStuff()
		{
			srand( (unsigned)time( NULL ) );	
	 
			// Construi o Root do Ogre
			mRoot.reset(new Ogre::Root(PLUGINS_CFG));
	 
			// Carregando as pastas dos resources
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/materials/scripts", "FileSystem", "Popular");
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/materials/textures", "FileSystem", "Popular");
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/models", "FileSystem", "Popular");
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem", "General");
				
			// mRoot->restoreConfig() Verifica se ja existe configuração no ogre.cfg
			// se existir retorna true e entra no if
			// senão cai no OU e mostra a tela para escolher configuração
			if(mRoot->restoreConfig() || mRoot->showConfigDialog())
			{
				// O primeiro parâmetro diz ao Ogre que ele pode criar uma janela para renderização
				// O segundo parâmetro é o titulo da Janela
				mWindow = mRoot->initialise(true, "Ponto V - Tutorial 1");
			}
			else
			{
				// Caso o usuário aperte cancel na tela do ogre feche o programa
				return false;
			}

			// Escolhendo o gerenciador de cenas
			mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
				
			// Cria a camera
			mCamera = mSceneMgr->createCamera("Camera");
	 
			// ViewPort é o que faz a cena ser renderizado pela camera
			Ogre::Viewport* vp = mWindow->addViewport(mCamera);
			// Cor de fundo do ViewPort
			vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	 
			// Muda o aspecto(width, height) da camera para se adequar ao ViewPort
			mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
			// Coloca o número padrão de MipMaps
			Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

			// Carrega Todos resoures
			Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
			
			return true;
		}

		void createBoxObject(const char *name, const Ogre::Vector3 &size, const Ogre::Vector3 &pos, float mass, btCollisionShape &shape)
		{
			//Criando um scene node para representar o objeto
			Ogre::SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);

			//criando o rigid body
			btRigidBody &body = mPhysics.createBody(btTransform(btQuaternion::getIdentity(), btVector3(pos.x, pos.y, pos.z)), mass, shape);


			//Criando um "Objeto de cena" com o scene node e o corpo rigido
			mObjects.push_back(new SceneObject(*node1, body));
			
			//Agora criamos um "cubo" para representar nosso objeto e associamos ele com o Scenenode
			Ogre::Entity *entity = mSceneMgr->createEntity(name, "Prefab_Cube");
			node1->attachObject(entity);

			//Por fim ajustamos o tamanho do cubo para ele ter a mesma dimensão do objeto físico
			node1->setScale(size.x / 100.0f, size.y / 100.0f, size.z / 100.0f);
		}

		void createObjects()
		{
			btCollisionShape &planeShape = mPhysics.createBoxShape(200, 1.0f, 200);
			btCollisionShape &cubeShape = mPhysics.createBoxShape(10, 10, 10);
			btCollisionShape &plane2Shape = mPhysics.createBoxShape(50, 1.0f, 50);

			createBoxObject("cube", Ogre::Vector3(10, 10, 10), Ogre::Vector3(0, 100, 0), 1, cubeShape);
			createBoxObject("cube2", Ogre::Vector3(10, 10, 10), Ogre::Vector3(0, 80, 0), 5, cubeShape);
			createBoxObject("cube3", Ogre::Vector3(10, 10, 10), Ogre::Vector3(0, 130, 0), 5, cubeShape);
			createBoxObject("cube4", Ogre::Vector3(10, 10, 10), Ogre::Vector3(30, 150, 0), 10, cubeShape);
			createBoxObject("plane2", Ogre::Vector3(50, 1, 50), Ogre::Vector3(20, 110, 0), 1, plane2Shape);

			createBoxObject("floor", Ogre::Vector3(200, 1, 200), Ogre::Vector3(0, -50, 0), 0, planeShape);		
		}

		bool runApplication()
		{			
			// Posiciona a Camera
			mCamera->setPosition(Ogre::Vector3(0, 0, 300));
			// Manda a camera olhar para um ponto
			mCamera->lookAt(Ogre::Vector3(0, 0, -300));
			// Distancia mínima para que o objeto deve estar da camera para ser renderziado
			mCamera->setNearClipDistance(5);
			// Distancia máxima para que o objeto deve estar da camera para ser renderziado
			mCamera->setFarClipDistance(5000);			

			createObjects();

			// Cria Luz ambiente
			mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	 
			// Cria uma Luz
			Ogre::Light* l = mSceneMgr->createLight("Luz");
			l->setPosition(20, 80, 50);				

			//Loop Principal
			for(;;)
			{
				// Processa as mensagens que o Sistema Operaciona envia para aplicação
				Ogre::WindowEventUtilities::messagePump();

				// Parar o programa caso a janela seja fechada
				if(mWindow->isClosed()){
					return false;
				}

				mPhysics.update(0.001);

				for(int i = 0, len = mObjects.size();i < len; ++i)
					mObjects[i]->prepareToRender();


				// Renderiza Um Frame
				if(!mRoot->renderOneFrame()) 
					return false;
			}
			return false;
		}
};
	
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
		Tutorial1 application;
        try 
		{
			if( application.initializeOgreStuff() )
			{
				application.runApplication();
			}
        } 
		catch( Ogre::Exception& e ) 
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif