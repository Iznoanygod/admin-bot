#ifndef _DISCORD_CLASS_H_
#define _DISCORD_CLSAS_H_

class DiscordClass : public SleepyDiscord::DiscordClient {
    public:
        using SleepyDiscord::DiscordClient::DiscordClient;
        void onMessage(SleepyDiscord::Message message) override {

        }
};

#endif
