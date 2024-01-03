// things.inc
//
// things plugin by Bombo v0.9 is needed
//
//

native create_things(in_filename[], in_host[], in_user[], in_pass[], in_database[]);
native composit_thing(request[], &out_main_thing_id);
native composit_thing_ex(request[], extra[], &out_main_thing_id);
native is_composit(object_id);

native init_thread_sql(host[], user[], pass[], database[]);
native stop_thread_sql();
native thread_sql(request[]);
