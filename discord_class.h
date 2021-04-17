#ifndef _DISCORD_CLASS_H_
#define _DISCORD_CLASS_H_

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    void onMessage(SleepyDiscord::Message message);
};
#endif
