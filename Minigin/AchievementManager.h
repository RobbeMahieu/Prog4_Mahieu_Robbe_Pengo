#pragma once
#include <steam_api.h>
#include <memory>
#include "Observer.h"
#include "AchievementList.h"
#include "Singleton.h"

namespace dae {
	class GameObject;
}

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

class CSteamAchievements final : public dae::Singleton<CSteamAchievements>
{
private:

	friend class Singleton<CSteamAchievements>;
	CSteamAchievements();

	uint64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?

	std::unique_ptr<Observer> m_WinnerAchievementListener;

	void WinnerAchievement(dae::GameObject* damagedObject);

public:
	void Initialize(Achievement_t* Achievements, int NumAchievements);
	~CSteamAchievements() = default;

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);
};