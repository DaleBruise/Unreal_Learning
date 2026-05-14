
#pragma once

#define NAME_TargetActor "TargetActor"

#define COLLISION_INTERACTION ECC_GameTraceChannel1
#define COLLISION_PROJECTILE ECC_GameTraceChannel2

inline TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDrawing"),
	false,
	TEXT("Enable interaction debug drawing"),
	ECVF_Cheat);


