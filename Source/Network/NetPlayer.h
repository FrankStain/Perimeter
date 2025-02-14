#ifndef __PERIMETER_PLAYER_H__
#define __PERIMETER_PLAYER_H__

#include "UnitAttribute.h"
#include "Serialization.h"

struct SavePrm;

enum RealPlayerType {
	REAL_PLAYER_TYPE_CLOSE,
	REAL_PLAYER_TYPE_OPEN,
	REAL_PLAYER_TYPE_PLAYER,
	REAL_PLAYER_TYPE_AI,
	REAL_PLAYER_TYPE_WORLD
};

DECLARE_ENUM_DESCRIPTOR(RealPlayerType)

struct PlayerData {
	enum  {
		PLAYER_ID_NONE = -1
	};
	
	int playerID;
	EnumWrapper<RealPlayerType> realPlayerType;
	EnumWrapper<terBelligerent> belligerent;
	int colorIndex;
	int clan;
	EnumWrapper<Difficulty> difficulty;
	int handicap;
	bool flag_playerStartReady;
	bool flag_playerGameReady;
	int compAndUserID;
	unsigned int gameVersion;
	char playerName[64];
	DPNID dpnid;
	
	PlayerData();
	PlayerData(int playerIDIn, const char* name, terBelligerent belligerentIn, int colorIndexIn, RealPlayerType realPlayerTypeIn = REAL_PLAYER_TYPE_PLAYER);

	void set(int playerIDIn, const char* name, terBelligerent belligerentIn, int colorIndexIn, RealPlayerType realPlayerTypeIn = REAL_PLAYER_TYPE_PLAYER);
	
	void setCompAndUserID(const char* computerName, const char* playerName){
		compAndUserID = calcCompAndUserID(computerName, playerName);
	}
	unsigned int calcCompAndUserID(const char* computerName, const char* playerName);

	const char* name() const { return playerName; } 
	void setName(const char* name) { strcpy(playerName, name); }

	void read(XBuffer& in);
	void write(XBuffer& out) const;

#include "NetPlayer-1251-1.inl"
};


enum GameType {
	GT_SINGLE_PLAYER,
	GT_SINGLE_PLAYER_NO_AI,
	GT_SINGLE_PLAYER_ALL_AI,
	GT_createMPGame,
	GT_loadMPGame,
	GT_playRellGame
};

class MissionDescription 
{
public:
	MissionDescription();
	MissionDescription(const char* save_name, GameType gameType = GT_SINGLE_PLAYER);
	void init();

	bool loadMission(SavePrm& savePrm) const; 
	bool saveMission(const SavePrm& savePrm, bool userSave) const; 
	void restart();

	void setSaveName(const char* name);
	void setReelName(const char* name);

	void read(XBuffer& in);
	void write(XBuffer& out) const;

	void simpleRead(XBuffer& in);
	void simpleWrite(XBuffer& out) const;

	const char* saveName() const { return saveName_.c_str(); }
	const char* saveNameBinary() const { return saveNameBinary_.c_str(); }
	const char* missionName() const { return missionName_.c_str(); }
	const char* missionDescription() const { return missionDescriptionStr_.c_str(); }

	int worldID() const { return worldID_; }

	bool isMultiPlayer() const { return gameType_ == GT_createMPGame || gameType_ == GT_loadMPGame;	}

	int playersAmountScenarioMax() const { return playerAmountScenarioMax; }
	int playersAmount() const;
	int playersMaxEasily() const;

	void packPlayerIDs();

	void clearAllPlayerStartReady(void);

	bool setPlayerStartReady(DPNID dpnid);
	bool isAllRealPlayerStartReady(void);
	void clearAllPlayerGameReady(void);

	void disconnect2PlayerData(int idxPlayerData);
	void connectAI2PlayersData(int idxPlayerData);
	int connectNewPlayer2PlayersData(PlayerData& pd, DPNID dpnid);
	int connectLoadPlayer2PlayersData(PlayerData& pd, DPNID dpnid);
	bool disconnectPlayer2PlayerDataByIndex(unsigned int idx);
	bool disconnectPlayer2PlayerDataByDPNID(DPNID dpnid);
	bool setPlayerDPNID(unsigned int idx, DPNID dpnid);

	int getUniquePlayerColor(int begColor=0, bool dirBack=0);
	bool changePlayerColor(int playerIdx, int color, bool dirBack=0);
	bool changePlayerColor(DPNID dpnid, int color, bool dirBack=0);

	bool changePlayerDifficulty(int playerIdx, Difficulty difficulty);
	bool changePlayerDifficulty(DPNID dpnid, Difficulty difficulty);

	int getUniquePlayerClan();
	bool changePlayerClan(int playerIdx, int clan);
	bool changePlayerClan(DPNID dpnid, int clan);

	bool changePlayerHandicap(int playerIdx, int handicap);
	bool changePlayerHandicap(DPNID dpnid, int handicap);

	void getAllOtherPlayerName(std::string& outStr);
	void getPlayerName(int _playerID, std::string& outStr);

	int findPlayer(DPNID dpnid);

	bool changePlayerBelligerent(int playerIdx, terBelligerent newBelligerent);
	bool changePlayerBelligerent(DPNID dpnid, terBelligerent newBelligerent);

	bool isChanged(void){return flag_missionDescriptionUpdate;}
	void setChanged(void){flag_missionDescriptionUpdate=true;}
	void clearChanged(void){flag_missionDescriptionUpdate=0;}

	void setSinglePlayerDifficulty(Difficulty difficuty);

	void shufflePlayers();

	PlayerData& getActivePlayerData();

#include "NetPlayer-1251-2.inl"

	PrmString version;
	PrmString worldName;
	CustomString missionDescriptionID;
	EnumWrapper<Difficulty> difficulty;
	PlayerData playersData[4];
	int missionNumber;
	int playerAmountScenarioMax;
	int playersShufflingIndices[4];
	int activePlayerID;
	int globalTime;
	float gameSpeed;
	bool gamePaused;
	PrmString originalSaveName;

	unsigned int quantAmountInPlayReel;
	std::string fileNamePlayReelGame;
	std::string missionNamePlayReelGame;
	GameType gameType_;
	bool flag_missionDescriptionUpdate;

private:
	int worldID_;
	std::string saveName_;
	std::string saveNameBinary_;
	std::string missionName_;
	std::string missionDescriptionStr_;
	unsigned int serverRnd_;
};

#endif
