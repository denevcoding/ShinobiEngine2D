#include "stdafx.h"
#include "World.h"
#include "../../Global/EngineSettings.h"
#include "../GameObjectx/GameObject.h"
#include "GraphicsEngine.h"
#include "../GameObjectx/Components/Transform2D.h"
#include "../GlobalObjects/Graphix/Background.h"
#include "../GameObjectx/Components/GraphicComponents/RenderComponent.h"
#include "../GameObjectx/Components/PhysicComponents/PhysixBody.h"
#include "../GameObjectx/Components/PhysicComponents/RectCollider.h"
#include "../GameObjectx/Components/PhysicComponents/CircleCollider.h"
#include "../GlobalObjects/Audiox/AudioClip.h"
#include "../GameObjectx/Components/AudioComponents/AudioSource.h"
#include "../GameObjectx/Components/AudioComponents/AudioListener.h"


#pragma region Singleton
World& World::GetInstance()
{
    static World world;
    return world;
}


//Constructor privado
World::World()
 :m_GameObjects(MaxEntities)

 , m_Background(nullptr)

 , m_TimeManager(TimeSettings::DeltaTime)
{
    m_GameObjects.clear();
}
#pragma endregion



void World::Init()
{
    //-------------------------background-----------------------------------
	#pragma region creating background
    Transform2D* p_transformBackground = new Transform2D(Vec2(0, 0), Vec2(1, 1));
    assert(p_transformBackground != nullptr);
    m_Background = new Background("../data/Graphics/roofs.png", 1, 1, p_transformBackground);
    assert(m_Background != nullptr);
    //registering renreable object in graphic engine
    GraphicsEngine::GetInstance().InsertRenderObj(*m_Background);

	//Adding Audio
	#pragma endregion
    //-------------------------background-----------------------------------

	#pragma region Ground
    GameObject* ground = new GameObject("Ground", "Ground");
    assert(ground != nullptr);

    //Setting up The basics
    Vec2 groundPosition = Vec2(GeneralSettings::WindowWidth / 2, GeneralSettings::WindowHeight);
    Vec2 groundScale = Vec2(1.0f, 1.0f);
    ground->m_transform_2d->SetPos(groundPosition);
    ground->m_transform_2d->SetScale(groundScale);

	#pragma region  Collision collider Component Settings
    //Setting the Collision Collider component
    PhysixMaterial groundPhxMaterial;
    //Setting Physix material
    groundPhxMaterial.density = 0.3f;
    groundPhxMaterial.restitution = 0.5f;
    groundPhxMaterial.staticFriction = 0.5f;
    groundPhxMaterial.dynamicFriction = 0.5f;

    Vec2 groundSize = Vec2(1280, 100);
    RectCollider* pGroundRectComp = new RectCollider(*ground->m_transform_2d, groundPhxMaterial, groundSize);
    assert(pGroundRectComp != nullptr);
	#pragma endregion


	#pragma region PhysixBody component Settings
    PhysixBody* pGroundPhysixBodyComponent = new PhysixBody(*ground->m_transform_2d, pGroundRectComp, true);
    assert(pGroundPhysixBodyComponent != nullptr);
	#pragma endregion

	#pragma region  Inserting Components and entitie
    ground->AddComponent<PhysixBody&>(*pGroundPhysixBodyComponent);
    ground->AddComponent<RectCollider&>(*pGroundRectComp);

    // Insert entity to wht world.
    m_GameObjects.push_back(ground);
    // Activation.
    ground->Activate();
	#pragma endregion	
	#pragma endregion GroundeEnd

	
    //-------------------------Ninja -Player---------------------------------	
	#pragma region Ninja Player
    GameObject* ninjaPlayer = new GameObject("Ninja", "Character");
    assert(ninjaPlayer != nullptr);

    //Setting up The basics
    Vec2 ninjaPosition = Vec2(GeneralSettings::WindowWidth / 2.5f, GeneralSettings::WindowHeight / 2.5);
    Vec2 ninjaScale = Vec2(0.7f, 0.7f);
    ninjaPlayer->m_transform_2d->SetPos(ninjaPosition);
    ninjaPlayer->m_transform_2d->SetScale(ninjaScale);

	#pragma region Render Component Settings
    // Setting render component. Cuadrar el update y los fps para animar - Sistema para blending - sistema para animacion y cosas estaticas
    RenderComponent* pRenderComp = new RenderComponent(ninjaPlayer->m_transform_2d, "../data/Graphics/ninja_anim.png", 10, 4);
    assert(pRenderComp != nullptr);
    //Graphic Settings Overriding default settings
    pRenderComp->m_Sprite.blendMode = BLEND_ALPHA;

    //Animation Settings
    //Animations
    Animation2D* idleNinja = new Animation2D("idle", 12, 0, 9);
    pRenderComp->m_Sprite.animationList.push_back(idleNinja);
    Animation2D* runNinja = new Animation2D("run", 24, 10, 10);
    pRenderComp->m_Sprite.animationList.push_back(runNinja);
    Animation2D* jumpNinja = new Animation2D("jump", 24, 21, 8);
    pRenderComp->m_Sprite.animationList.push_back(jumpNinja);
    Animation2D* parachuteNinja = new Animation2D("parachute", 12, 30, 10);
    pRenderComp->m_Sprite.animationList.push_back(parachuteNinja);
    //Setting the current animation
    pRenderComp->m_Sprite.m_currentAnimation = *runNinja;
	#pragma endregion

	#pragma region  Collision collider Component Settings
    //Setting the Collision Collider component
    PhysixMaterial ninjaPhisixMaterial;
    //Setting Physix material
    ninjaPhisixMaterial.density = 0.5f;
    ninjaPhisixMaterial.restitution = 0.99f;

    ninjaPhisixMaterial.staticFriction = 0.5f;
    ninjaPhisixMaterial.dynamicFriction = 0.5f;

    Vec2 size = Vec2(pRenderComp->m_Sprite.frameWidth, pRenderComp->m_Sprite.frameHeight);
    RectCollider* pRectComp = new RectCollider(*ninjaPlayer->m_transform_2d, ninjaPhisixMaterial, size);
    assert(pRectComp != nullptr);
	#pragma endregion
	
	#pragma region PhysixBody component Settings
    PhysixBody* pPhysixBodyComponent = new PhysixBody(*ninjaPlayer->m_transform_2d, pRectComp, false);
    assert(pPhysixBodyComponent != nullptr);
    pPhysixBodyComponent->gravityScale = 1.f;
    pPhysixBodyComponent->m_vVel = Vec2(5.f, 0.f);
	#pragma endregion

	#pragma region AudioComponent Settings
    AudioClip* Song = new  AudioClip("../data/Audio/music.wav");
    assert(Song != nullptr);
    AudioSource* pAudioSourceComponent = new AudioSource(*ninjaPlayer->m_transform_2d, Song, true);
    assert(pAudioSourceComponent != nullptr);
	#pragma endregion

//#pragma region AudioComponent Settings
//    AudioListener* pAudioListenerComponent = new AudioListener(*ninjaPlayer->m_transform_2d);
//    assert(pAudioListenerComponent != nullptr);
//#pragma endregion

	#pragma region  Inserting Components and entitie
    ninjaPlayer->AddComponent<PhysixBody&>(*pPhysixBodyComponent);
    ninjaPlayer->AddComponent<RectCollider&>(*pRectComp);
    ninjaPlayer->AddComponent<RenderComponent&>(*pRenderComp);
    ninjaPlayer->AddComponent<AudioSource&>(*pAudioSourceComponent);
   // ninjaPlayer->AddComponent<AudioListener&>(*pAudioListenerComponent);

    // Insert entity.
    m_GameObjects.push_back(ninjaPlayer);
    // Activation.
    ninjaPlayer->Activate();
	#pragma endregion
	#pragma endregion Ninja End
    //-------------------------Ninja - Player---------------------------------


	
   
	
    //-------------------------Soccer Ball-----------------------------------
	#pragma region SoccerBall
    GameObject* soccerBall = new GameObject("SoccerBall", "Ball");
    assert(soccerBall != nullptr);

    //Setting up The basics
    Vec2 ballPosition = Vec2(GeneralSettings::WindowWidth / 2.5f, GeneralSettings::WindowHeight / 1.5);
    Vec2 ballScale = Vec2(1.0f, 1.0f);
    soccerBall->m_transform_2d->SetPos(ballPosition);
    soccerBall->m_transform_2d->SetScale(ballScale);

	#pragma region Render Component Settings
    RenderComponent* pBallRenderComp = new RenderComponent(soccerBall->m_transform_2d, "../data/Graphics/ball.png", 1, 1);
    assert(pBallRenderComp != nullptr);
    //Graphic Settings Overriding default settings
    pBallRenderComp->m_Sprite.blendMode = BLEND_ALPHA;
	#pragma endregion

	#pragma region  Collision collider Component Settings
    //Setting the Collision Collider component
    PhysixMaterial BallPhisixMaterial;
    //Setting Physix material
    BallPhisixMaterial.density = 0.3f;
    BallPhisixMaterial.restitution = 0.99f;

    BallPhisixMaterial.staticFriction = 0.3f;
    BallPhisixMaterial.dynamicFriction = 0.3f;

    float ballRadius = pBallRenderComp->m_Sprite.frameWidth/2;
    CircleCollider* pBallCircleCollider = new CircleCollider(*soccerBall->m_transform_2d, BallPhisixMaterial, ballRadius);
    assert(pBallCircleCollider != nullptr);
	#pragma endregion

	#pragma region PhysixBody component Settings
    PhysixBody* pBallBodyComponent = new PhysixBody(*soccerBall->m_transform_2d, pBallCircleCollider, true);
    assert(pBallBodyComponent != nullptr);
    pBallBodyComponent->gravityScale = 1.f;
    pBallBodyComponent->m_isEnabled = false;
	#pragma endregion

	#pragma region  Inserting Components and entitie
    soccerBall->AddComponent<PhysixBody&>(*pBallBodyComponent);
    soccerBall->AddComponent<CircleCollider&>(*pBallCircleCollider);
    soccerBall->AddComponent<RenderComponent&>(*pBallRenderComp);
    // Insert entity.
    m_GameObjects.push_back(soccerBall);
    // Activation.
    soccerBall->Activate();
	#pragma endregion	
	#pragma endregion
	//-------------------------Soccer Ball-----------------------------------


     //-------------------------Colliders prueba------------------------------
	#pragma region Box Collider
    GameObject* boxPlayer = new GameObject("Box", "Boxitas");
    assert(boxPlayer != nullptr);
    Vec2 boxPosition = Vec2(GeneralSettings::WindowWidth / 1.5, GeneralSettings::WindowHeight / 1.5);
    Vec2 boxScale = Vec2(1.0f, 1.0f);
    boxPlayer->m_transform_2d->SetPos(boxPosition);
    boxPlayer->m_transform_2d->SetScale(boxScale);

	#pragma region Box Render component
    //Setting render component. Cuadrar el update y los fps para animar - Sistema para blending - sistema para animacion y cosas estaticas
    RenderComponent* pBoxRenderComp = new RenderComponent(boxPlayer->m_transform_2d, "../data/Graphics/box.png", 1, 1);
    assert(pBoxRenderComp != nullptr);
    //Graphic Settings Overriding default settings
    pBoxRenderComp->m_Sprite.blendMode = BLEND_SOLID;
	#pragma endregion

	#pragma region  Collision collider Component Settings	
    //Setting the Collision Collider component
    PhysixMaterial boxPhisixMaterial;
    //Setting Physix material
    boxPhisixMaterial.density = 0.3;
    boxPhisixMaterial.restitution = 0.8f;

    boxPhisixMaterial.staticFriction = 0.5;
    boxPhisixMaterial.dynamicFriction = 0.5;


    Vec2 sizeBox = Vec2(pBoxRenderComp->m_Sprite.frameWidth, pBoxRenderComp->m_Sprite.frameHeight);
    RectCollider* pRectBoxComp = new RectCollider(*boxPlayer->m_transform_2d, boxPhisixMaterial, sizeBox);
    assert(pRectBoxComp != nullptr);
	#pragma endregion

	#pragma region PhysixBody component Settings
    PhysixBody* pBoxBodyComponent = new PhysixBody(*boxPlayer->m_transform_2d, pRectBoxComp, true);
    assert(pBoxBodyComponent != nullptr);
	#pragma endregion

	#pragma region AudioComponent Settings
    AudioListener* pAudioListenerComponent = new AudioListener(*boxPlayer->m_transform_2d);
    assert(pAudioListenerComponent != nullptr);
	#pragma endregion

	#pragma region  Inserting Box to the world
    boxPlayer->AddComponent<PhysixBody&>(*pBoxBodyComponent);
    boxPlayer->AddComponent<RectCollider&>(*pRectBoxComp);
    boxPlayer->AddComponent<RenderComponent&>(*pBoxRenderComp);
    boxPlayer->AddComponent<AudioListener&>(*pAudioListenerComponent);

    // Insert entity.
    m_GameObjects.push_back(boxPlayer);
    boxPlayer->Activate();
	#pragma endregion
	#pragma endregion
    //-------------------------Colliders prueba------------------------------


    //-------------------------Tyrian Ball-----------------------------------
	#pragma region TyrianBall
    GameObject* TyrianBall = new GameObject("TyrianBall", "Balls");
    assert(TyrianBall != nullptr);

    //Setting up The basics
    Vec2 tyBallPosition = Vec2(GeneralSettings::WindowWidth/1.5, GeneralSettings::WindowHeight /4);
    Vec2 tyBallScale = Vec2(1.0f, 1.0f);
    TyrianBall->m_transform_2d->SetPos(tyBallPosition);
    TyrianBall->m_transform_2d->SetScale(tyBallScale);

	#pragma region Render Component Settings
    RenderComponent* pTyBallRenderComp = new RenderComponent(TyrianBall->m_transform_2d, "../data/Graphics/tyrian_ball.png", 1, 1);
    assert(pTyBallRenderComp != nullptr);
    //Graphic Settings Overriding default settings
    pTyBallRenderComp->m_Sprite.blendMode = BLEND_ALPHA;
	#pragma endregion

	#pragma region  Collision collider Component Settings
    //Setting the Collision Collider component
    PhysixMaterial tyBallPhisixMaterial;
    //Setting Physix material
    tyBallPhisixMaterial.density = 0.6f;
    tyBallPhisixMaterial.restitution = 0.8f;

    tyBallPhisixMaterial.staticFriction = 0.3f;
    tyBallPhisixMaterial.dynamicFriction = 0.3f;
   

    float tyBallRadius = pTyBallRenderComp->m_Sprite.frameWidth / 2;
    CircleCollider* pTyBallCircleCollider = new CircleCollider(*TyrianBall->m_transform_2d, tyBallPhisixMaterial, tyBallRadius);
    assert(pTyBallCircleCollider != nullptr);
	#pragma endregion

	#pragma region PhysixBody component Settings
    PhysixBody* pTyBallBodyComponent = new PhysixBody(*TyrianBall->m_transform_2d, pTyBallCircleCollider, false);
    assert(pTyBallBodyComponent != nullptr);
    //pTyBallBodyComponent->m_bUseGravity = false;
    pTyBallBodyComponent->gravityScale = 3.f;
    pTyBallBodyComponent->m_vVel = Vec2(-15.f, 0.f);
	#pragma endregion

	#pragma region  Inserting Components and entitie
    TyrianBall->AddComponent<PhysixBody&>(*pTyBallBodyComponent);
    TyrianBall->AddComponent<CircleCollider&>(*pTyBallCircleCollider);
    TyrianBall->AddComponent<RenderComponent&>(*pTyBallRenderComp);
    // Insert entity.
    m_GameObjects.push_back(TyrianBall);
    // Activation.
    TyrianBall->Activate();
	#pragma endregion	
	#pragma endregion TyrianBall
    //-------------------------Tyrian Ball-----------------------------------
	
	
    //-------------------------Bee - Player---------------------------------
	#pragma region Bee Character
    GameObject* beePlayer = new GameObject("Bee", "Character");
    assert(beePlayer != nullptr);

    //Setting up The basics
    Vec2 beePosition = Vec2(GeneralSettings::WindowWidth / 2, GeneralSettings::WindowHeight / 2);
    Vec2 beeScale = Vec2(0.7f, 0.7f);
    beePlayer->m_transform_2d->SetPos(beePosition);
    beePlayer->m_transform_2d->SetScale(beeScale);
	
	#pragma region Render Component Settings
    // Setting render component. Cuadrar el update y los fps para animar - Sistema para blending - sistema para animacion y cosas estaticas
    RenderComponent* pRenderBeeComp = new RenderComponent(beePlayer->m_transform_2d, "../data/Graphics/bee_anim.png", 8, 1);
    assert(pRenderBeeComp != nullptr);
    //Graphic Settings Overriding default settings
    pRenderBeeComp->m_Sprite.blendMode = BLEND_ALPHA;
	
    //Animation Settings
    Animation2D* flyingBee = new Animation2D("flying", 24, 0, 8);
    pRenderBeeComp->m_Sprite.animationList.push_back(flyingBee);
	
    //Setting the current animation
    pRenderBeeComp->m_Sprite.m_currentAnimation = *pRenderBeeComp->m_Sprite.animationList.front();
	#pragma endregion

	#pragma region  Inserting Components and entitie
    beePlayer->AddComponent<RenderComponent&>(*pRenderBeeComp);
    // Insert entity.
    m_GameObjects.push_back(beePlayer);
    // Activation.
    beePlayer->Activate();
	#pragma endregion
	#pragma endregion Bee End
    //-------------------------Bee - Player---------------------------------	
}


//Main Loop on World
void World::Update()
{
    //Calls Timer to process logic slot
    m_TimeManager.InitSlotsToProcess();
    while (m_TimeManager.ProcessSlots())
    {
        UpdateObjects(m_TimeManager.GetFixedTick());
    }
}


//Update de los game objects
void World::UpdateObjects(double fDeltaTime)
{
    //Update Entities
    for (GameObject* gObject : m_GameObjects)
    {
        assert(gObject != nullptr);
	    if (gObject->m_isEnabled == true)
	    {
            gObject->Update(fDeltaTime);
	    }      
    }
}


void World::Terminate()
{
    for (GameObject* gObject : m_GameObjects)
    {
        assert(gObject != nullptr);

        if (gObject != nullptr)
        {
            gObject->Deactivate();
            //delete gObject;
        }
    }
    m_GameObjects.clear();
    //Derreregistering renreable object in graphics engine
    GraphicsEngine::GetInstance().DeleteRenderObj(*m_Background);
	//include Audio Engine para borrar los audios
}