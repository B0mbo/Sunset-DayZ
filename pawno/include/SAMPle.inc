/* 
    Bombo translate functions
*/

#if defined _TRANSLATE_FUNCS
	#endinput
#endif

#define _TRANSLATE_FUNCS

native init_translate();
native stop_translate();
native new_translate();
native translate(out_text[], in_text[], in_lang_from[], in_lang_to[], size=sizeof out_text);
native translate_id(out_text[], in_text[], in_playerid_from, in_playerid_to, fnick=1, size=sizeof out_text);
native translate_cached(out_text[], in_text[], in_lang_from[], in_lang_to[], fnick=1, size=sizeof out_text);
native translate_nick(out_text[], in_text[], in_lang_from[], in_lang_to[], size=sizeof out_text);
native language(in_ip_addr[], out_lang[], out_country[], out_city[]);
native getplayerlang(in_playerid, out_lang[]);
native setplayerlang(in_playerid, in_lang[]);
native getplayerland(in_playerid, out_land[]);
native setplayerland(in_playerid, in_land[]);
native add_nick(in_nick[]);
native add_nick_id_ip(in_nick[], in_playerid, in_ip_addr[]);
native add_nick_id_ip_land_lang(in_nick[], in_playerid, in_ip_addr[], out_land[], out_lang[], out_country[], out_city[]);
native del_nick(in_nick[]);
native del_all_players();
native init_ifile(in_filename[]);
native close_ifile();
native imessage(out_text[], in_name[], in_language[], size=sizeof out_text);
native default_language(in_def_lang[]);

native init_antimat(in_words[]);
native stop_antimat();
native antimat(out_text[], in_text[], in_lang[], size=sizeof(out_text));
