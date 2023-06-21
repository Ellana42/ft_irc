
/* #include "test.hpp" */
/* #include "Context.hpp" */
/* #include "Password.hpp" */

/* #define SOCKET_A 1 */
/* #define SOCKET_B 2 */
/* #define SOCKET_C 3 */
/* #define SOCKET_D 4 */

/* void run_test_suite( void ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING FT_IRC" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	std::cout << CYAN "-- Creating context" RESET << std::endl; */
/* 	Password * passwords = new Password( "test" ); */
/* 	Context & context = *( new Context( *passwords ) ); */

/* 	create_new_user( context, SOCKET_A ); */
/* 	create_new_user( context, SOCKET_B ); */
/* 	create_new_user( context, SOCKET_C ); */
/* 	create_new_user( context, SOCKET_D ); */

/* 	print_users_status( context ); */

/* 	test_preregistration_security( context ); */
/* 	test_user_before_registration( context ); */
/* 	test_register_users( context ); */
/* 	test_user_after_registration( context ); */
/* 	test_nick( context ); */
/* 	test_admin_info( context ); */
/* 	test_summon_users( context ); */
/* 	test_user_privmsg( context ); */
/* 	test_names( context ); */
/* 	test_join( context ); */
/* 	test_names( context ); */
/* 	test_part( context ); */
/* 	test_names( context ); */
/* 	test_mode( context ); */
/* 	test_list( context ); */
/* 	test_quit( context ); */

/* 	std::cout << CYAN "-- Deleting context" RESET << std::endl; */
/* 	delete ( &context ); */
/* } */

/* void test_register_users( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING USER REGISTRATION" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_socket( SOCKET_A ); */
/* 	User & bob = context.get_user_by_socket( SOCKET_B ); */
/* 	User & chloe = context.get_user_by_socket( SOCKET_C ); */
/* 	User & dante = context.get_user_by_socket( SOCKET_D ); */

/* 	send_test_message( context, alice, "USER alice alice alice alice\r\n" ); */
/* 	send_test_message( context, alice, "USER alice alice alice alice\r\n" ); */
/* 	send_test_message( context, alice, "NICK alice\r\n" ); */

/* 	print_users_status( context ); */

/* 	send_test_message( context, bob, "NICK bob\r\n" ); */
/* 	send_test_message( context, bob, "USER bob bob bob bob\r\n" ); */

/* 	print_users_status( context ); */

/* 	send_test_message( context, chloe, "NICK chloe\r\n" ); */
/* 	send_test_message( context, chloe, "USER chloe chloe chloe chloe\r\n" ); */

/* 	print_users_status( context ); */

/* 	send_test_message( context, dante, "NICK dante\r\n" ); */
/* 	send_test_message( context, dante, "ADMIN\r\n" ); */
/* 	send_test_message( context, dante, "USER dante dante dante dante\r\n" ); */

/* 	print_users_status( context ); */
/* } */

/* void test_preregistration_security( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING PRE-REGISTRATION SECURITY" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_socket( SOCKET_A ); */
/* 	User & bob = context.get_user_by_socket( SOCKET_B ); */

/* 	send_test_message( context, alice, "PRIVMSG bob hi\r\n" ); */
/* 	send_test_message( context, alice, "JOIN #test\r\n" ); */
/* 	send_test_message( context, alice, "PART #test\r\n" ); */
/* 	send_test_message( context, bob, "ADMIN\r\n" ); */
/* 	send_test_message( context, bob, "INFO\r\n" ); */
/* 	send_test_message( context, bob, "NAMES\r\n" ); */

/* } */

/* void test_user_before_registration( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING USER BEFORE REGISTRATION" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_socket( SOCKET_A ); */

/* 	send_test_message( context, alice, "USER a\r\n" ); */
/* 	send_test_message( context, alice, "USER a a a a a\r\n" ); */
/* 	send_test_message( context, alice, "USER 3a a a a\r\n" ); */
/* 	send_test_message( context, alice, "USER a- a a a\r\n" ); */
/* } */

/* void test_user_after_registration( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING USER AFTER REGISTRATION" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */

/* 	send_test_message( context, alice, "USER a\r\n" ); */
/* 	send_test_message( context, alice, "USER a a a a a\r\n" ); */
/* 	send_test_message( context, alice, "USER 3a a a a\r\n" ); */
/* 	send_test_message( context, alice, "USER a- a a a\r\n" ); */
/* 	send_test_message( context, alice, "USER x x x x\r\n" ); */
/* } */

/* void test_nick( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING NICK" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */

/* 	send_test_message( context, alice, "NICK\r\n" ); */
/* 	send_test_message( context, alice, "NICK al ice\r\n" ); */
/* 	send_test_message( context, alice, "NICK 123\r\n" ); */
/* 	send_test_message( context, alice, "NICK 1alice\r\n" ); */
/* 	send_test_message( context, alice, "NICK a-lice\r\n" ); */
/* 	send_test_message( context, alice, "NICK @lice\r\n" ); */
/* 	send_test_message( context, alice, "NICK :ali ce\r\n" ); */
/* 	send_test_message( context, alice, "NICK aaaaaaaaaa\r\n" ); */
/* 	send_test_message( context, alice, "NICK alice1234\r\n" ); */
/* 	send_test_message( context, alice, "NICK alice\r\n" ); */
/* 	send_test_message( context, bob, "NICK alice\r\n" ); */
/* 	send_test_message( context, bob, "NICK\r\n" ); */
/* 	send_test_message( context, bob, "NICK x x x\r\n" ); */
/* } */

/* void test_admin_info( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING ADMIN & INFO" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */

/* 	send_test_message( context, alice, "ADMIN\r\n" ); */
/* 	send_test_message( context, alice, "INFO\r\n" ); */
/* 	send_test_message( context, alice, "INFO hello\r\n" ); */
/* 	send_test_message( context, alice, "ADMIN hello\r\n" ); */
/* } */

/* void test_summon_users( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING SUMMON & USERS" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */

/* 	send_test_message( context, alice, "SUMMON\r\n" ); */
/* 	send_test_message( context, alice, "USERS\r\n" ); */
/* 	send_test_message( context, alice, "SUMMON hello\r\n" ); */
/* 	send_test_message( context, alice, "USERS hello\r\n" ); */
/* } */

/* void test_user_privmsg( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING USER-TO-USER PRIVMSG" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */
/* 	User & chloe = context.get_user_by_nick( "chloe" ); */
/* 	User & dante = context.get_user_by_nick( "dante" ); */

/* 	send_test_message( context, alice, "PRIVMSG bob\r\n" ); */
/* 	send_test_message( context, bob, "PRIVMSG alice hi I'm bob\r\n" ); */
/* 	send_test_message( context, alice, "PRIVMSG bob hello\r\n" ); */
/* 	send_test_message( context, bob, "PRIVMSG alice :hi I'm bob\r\n" ); */
/* 	send_test_message( context, chloe, "PRIVMSG alice :what's up?\r\n" ); */
/* 	send_test_message( context, dante, "PRIVMSG bob ?\r\n" ); */
/* 	send_test_message( context, dante, "PRIVMSG john :hi?\r\n" ); */
/* } */

/* void test_names( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING NAMES" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */

/* 	send_test_message( context, alice, "NAMES\r\n" ); */
/* 	send_test_message( context, bob, "NAMES\r\n" ); */
/* 	send_test_message( context, bob, "NAMES #test\r\n" ); */
/* 	send_test_message( context, alice, "NAMES #test,#hello\r\n" ); */
/* } */

/* void test_join( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING JOIN" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */
/* 	User & chloe = context.get_user_by_nick( "chloe" ); */
/* 	User & dante = context.get_user_by_nick( "dante" ); */

/* 	send_test_message( context, bob, "JOIN\r\n" ); */
/* 	send_test_message( context, bob, "JOIN #test #hello #all\r\n" ); */
/* 	send_test_message( context, alice, "JOIN test\r\n" ); */
/* 	send_test_message( context, alice, "JOIN :#te st\r\n" ); */
/* 	send_test_message( context, alice, "JOIN :#t,est\r\n" ); */
/* 	send_test_message( context, alice, */
/* 	                   "JOIN :#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\r\n" ); */
/* 	send_test_message( context, alice, "JOIN &test\r\n" ); */
/* 	send_test_message( context, alice, "JOIN !test\r\n" ); */
/* 	send_test_message( context, alice, "JOIN +test\r\n" ); */
/* 	send_test_message( context, alice, "JOIN @test\r\n" ); */
/* 	send_test_message( context, alice, "JOIN :#TeSt\r\n" ); */

/* 	send_test_message( context, bob, "JOIN #test,#HELLO\r\n" ); */
/* 	send_test_message( context, alice, "JOIN #hello\r\n" ); */
/* 	send_test_message( context, chloe, "JOIN #hello,+Test\r\n" ); */
/* 	send_test_message( context, dante, "JOIN #TEST,+TEST\r\n" ); */
/* } */

/* void test_part( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING PART" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */


/* 	send_test_message( context, bob, "PART\r\n" ); */
/* 	send_test_message( context, bob, "JOIN 0\r\n" ); */
/* 	/1* send_test_message( context, bob, "PART #hello #test\r\n" ); *1/ */
/* 	send_test_message( context, alice, "PART #doesnotexist :bye\r\n" ); */
/* 	send_test_message( context, alice, "PART #test,!test,&test,+test :bye\r\n" ); */
/* 	send_test_message( context, alice, "PART #test :bye\r\n" ); */
/* 	/1* send_test_message( context, bob, "PART #test,#hello\r\n" ); *1/ */
/* } */

/* void test_quit( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING QUIT" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & bob = context.get_user_by_nick( "bob" ); */
/* 	User & chloe = context.get_user_by_nick( "chloe" ); */
/* 	User & dante = context.get_user_by_nick( "dante" ); */

/* 	send_test_message( context, alice, "JOIN #test,#hello\r\n" ); */
/* 	send_test_message( context, bob, "JOIN #test,#hello\r\n" ); */
/* 	send_test_message( context, alice, "QUIT bye bye\r\n" ); */
/* 	send_test_message( context, alice, "QUIT :bye bye\r\n" ); */
/* 	send_test_message( context, bob, "QUIT :see ya !\r\n" ); */

/* 	send_test_message( context, chloe, "QUIT\r\n" ); */
/* 	send_test_message( context, dante, "QUIT\r\n" ); */
/* } */

/* void test_mode( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING MODE" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */
/* 	User & dante = context.get_user_by_nick( "dante" ); */

/* 	context.create_channel( alice, "#achannel" ); */

/* 	Channel & channel = context.get_channel_by_name( "#achannel" ); */

/* 	std::cout << "Modes alice : " << alice.get_mode() << std::endl; */
/* 	send_test_message( context, alice, "MODE alice +abc-efg+ad\r\n" ); */
/* 	std::cout << "Modes alice : " << alice.get_mode() << std::endl; */
/* 	send_test_message( context, alice, "MODE alice +x-da+t\r\n" ); */
/* 	std::cout << "Modes alice : " << alice.get_mode() << std::endl; */
/* 	send_test_message( context, alice, "MODE alice +o-O\r\n" ); */
/* 	std::cout << "Modes alice : " << alice.get_mode() << std::endl; */

/* 	std::cout << "Modes channel" << channel.get_mode() << std::endl; */
/* 	send_test_message( context, alice, "MODE #achannel +abc-efg+ad\r\n" ); */
/* 	std::cout << "Modes channel : " << channel.get_mode() << std::endl; */
/* 	send_test_message( context, alice, "MODE #achannel +x-da+t\r\n" ); */
/* 	std::cout << "Modes channel : " << channel.get_mode() << std::endl; */

/* 	channel.add_user( dante ); */
/* 	/1* std::cout << "Channel modes alice : " << channel.get_user_modes( *1/ */
/* 	/1*               alice ) << std::endl; *1/ */
/* 	/1* std::cout << "Channel modes dante : " << channel.get_user_modes( *1/ */
/* 	/1*               dante ) << std::endl; *1/ */
/* 	/1* send_test_message( context, dante, "MODE #achannel +o alice\r\n" ); *1/ */
/* 	/1* std::cout << "Channel modes alice : " << channel.get_user_modes( *1/ */
/* 	/1*               alice ) << std::endl; *1/ */
/* 	/1* send_test_message( context, alice, "MODE #achannel +o \r\n" ); *1/ */
/* 	/1* send_test_message( context, alice, "MODE #achannel +o dante\r\n" ); *1/ */
/* 	/1* std::cout << "Channel modes dante : " << channel.get_user_modes( *1/ */
/* 	/1*               dante ) << std::endl; *1/ */
/* 	/1* send_test_message( context, dante, "MODE #achannel -o alice\r\n" ); *1/ */
/* 	/1* std::cout << "Channel modes alice : " << channel.get_user_modes( *1/ */
/* 	/1*               alice ) << std::endl; *1/ */
/* 	/1* send_test_message( context, alice, "MODE #achannel -o dante\r\n" ); *1/ */
/* 	/1* std::cout << "Channel modes dante : " << channel.get_user_modes( *1/ */
/* 	/1*               dante ) << std::endl; *1/ */

/* 	// TODO: overload << operator for user and channels */
/* } */

/* void test_list( Context & context ) */
/* { */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl; */
/* 	std::cout << CYAN "\t TESTING MODE" RESET << std::endl; */
/* 	std::cout << CYAN "-----------------------------------------------" RESET << */
/* 	          std::endl << std::endl; */

/* 	User & alice = context.get_user_by_nick( "alice" ); */

/* 	send_test_message( context, alice, "LIST\r\n" ); */
/* 	context.create_channel( alice, "#channel1" ); */
/* 	context.create_channel( alice, "#channel2" ); */
/* 	send_test_message( context, alice, "LIST\r\n" ); */
/* 	send_test_message( context, alice, "LIST #channel1\r\n" ); */
/* } */

/* void create_new_user( Context & context, int socket ) */
/* { */
/* 	std::cout << CYAN "-- Creating unregistered user on socket [" << socket << "]" */
/* 	          RESET << std::endl; */
/* 	context.create_unregistered_user( socket ); */
/* } */

/* void print_users_status( Context & context ) */
/* { */
/* 	std::cout << CYAN "-------------" RESET << std::endl; */
/* 	context.debug_print_unregistered_users(); */
/* 	context.debug_print_registered_users(); */
/* 	std::cout << CYAN "-------------" RESET << std::endl; */
/* } */

/* void send_test_message( Context & context, User & sender, std::string command ) */
/* { */
/* 	std::cout << CYAN "-- " << sender << " : " << command << RESET << std::endl; */
/* 	context.handle_message( sender, command ); */
/* 	std::cout << std::endl; */
/* } */
