/*
*
*  sampicq.inc by Bombo
*
*/

#if defined _SAMP_ICQ
	#endinput
#endif
#define _SAMP_ICQ

native icqconnect();                        //start ICQ-chat-bot
native icqdisconnect();                     //stop ICQ-chat-bot
native icqsendmessage(in_text[]);           //send message to ICQ-chat-bot
native icqsendtoname(in_name[], in_text[]); //send PM message to <in_name>
native icqsendonuin(in_uin[], in_text[]);   //send PM on UIN
forward OnICQMessage(from[], icqmes[]);     //incoming message callback
