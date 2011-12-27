// InputOutput.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include <ctime>
#include <iomanip>
#include <fstream>
#include "InputOutput.hpp"

namespace CM {
  
  bool IsSpaceOrComma(char ch) {
    return ch == ' ' || ch == ',';
  }
  
  std::string Plural(int n, std::string str) {
    if (n == 1) return str;
    else return str + 's';
  }
  
  InputOutput::InputOutput(std::ostream& out)
   : output(out),
     lastMessage("Please enter the tile to start, and good luck!") {
    engine.ResetGame();
  }
  
  InputOutput::InputOutput(std::istream* in, std::ostream& out)
   : input(in), output(out),
     lastMessage("Please enter the tile to start, and good luck!") {
    engine.ResetGame();
  }
  
  InputOutput::~InputOutput() { }
  
  void InputOutput::InitializeGame() {
    output <<
"+-----------------------------------------------------------------------------+\n" <<
"|                                   CodeMines                                 |\n" <<
"|                                By Peter Schultz                             |\n" <<
"+-----------------------------------------------------------------------------+\n" <<
"| Welcome to CodeMines!                                                       |\n" <<
"|    I, Peter Schultz, made this game in 100% standard C++ in the course of   |\n" <<
"|  about a week. This game is partly a cure for my insane level of boredom,   |\n" <<
"|  but it also provides a rather nice training utility for students learning  |\n" <<
"|  C++. Students may ask, \"What can I make with my new knowledge of C++?\"     |\n" <<
"|  Well, you can make a crude console game! Games are always good exercises,  |\n" <<
"|  due to the fact they can use a number of C++ utilities.                    |\n" <<
"|    Questions? Comments? Find me on IRC at irc.freenode.net. I'll be in the  |\n" <<
"|  channel \"##c++-social\" under the nickname \"Kaedenn\". Questions,            |\n" <<
"|  comments, opinions, bugs, etc. are all welcome! I love to receive input    |\n" <<
"|  about the programs I make.                                                 |\n" <<
"|    Now, if you've played Minesweeper, then this game should come naturally. |\n" <<
"|  To select a tile, enter the row number (from 1 to 20) followed by the      |\n" <<
"|  column letter (from A to Z). Letters are not case-sensitive, so 'A' is the |\n" <<
"|  same as 'a', and they both work. To \"mark\" or \"flag\" a tile, type the      |\n" <<
"|  word \"MARK\" or \"FLAG\", followed by the tile. Ex: \"FLAG 10A\" will mark      |\n" <<
"|  the tile 10 rows down and on the first column. Commas and spaces don't     |\n" <<
"|  matter, so \"10A\" is the same as \"10 , a\". Furthermore, you can swap the    |\n" <<
"|  row number and column letter, so \"A10\" is the same as \"10A\".               |\n" <<
"|    Other commands: SETMINES #, RESTART, QUIT. With SETMINES, replace # with |\n" <<
"|  a number between 1 and 520. Ex: \"SETMINES 200\" will restart the game with  |\n" <<
"|  200 mines.                                                                 |\n" <<
"|    There are a few \"Easter Eggs\" in this game, and two cheat codes... see   |\n" <<
"|  if you can find them!                                                      |\n" <<
"+-----------------------------------------------------------------------------+\n" <<
"|  Press ENTER or RETURN to begin the game with 20 rows, 26 columns and 50    |\n" <<
"|    mines. Good luck!                                                        |\n" <<
"+-----------------------------------------------------------------------------+\n";
    PauseForInput();
  }
  
  void InputOutput::RunGameLoop() {
    engine.SetMode(GameEngine::Playing);
    while (true) {
      Redraw();
      std::string command = toLower(GetCommand());
      if (command == "quit") {
        return;
      } else if (command == "restart") {
        engine.ResetGame();
        lastMessage = "Game restarted";
        continue;
      } else if (command == "longcat") {
        lastMessage = "Yes, longcat is loooooooooooooooong, and tacgnol is BLACK!";
      } else if (command == "desu") {
        lastMessage = "\n                      MMM         MMM                       \n                   MM   77:77777::7~  MM                    \n                 M  7:7:::::7:77::::7:7  M                  \n               M  7::::::::::7:::::::::77  M                \n              M  ::::::7::OOOOOOO::7:::7:7  MM              \n            M   7:::7OZIIIIIIIIIIIIIZO7::777  M             \n           M  ~:::OZIIIIIIIIIIIIOZIIIIIIO::7~  M            \n          M   :::OIIIIIIIIIIIIZIOZZIIIIIIZ:::~  MM          \n         M   ~:7ZIIIIIIIIOIIIIOIOOOIIIIIIIZ::7   M          \n        M    ~7OIIIIOIIIOZIZIZOOZ::ZIIOIIIIZ77    M         \n        MM~~ 77IIIII8888OZZZZ:Z:Z:::8888IIII77 ~~~M         \n          M~~7OIIIIOZZO:ZIZZ:.OOO:.:OZZZIZIIO+~~M           \n            M7OIIZIZZO:.ZZ::.O:O:...::ZZIIIIO7MM            \n             MOIZZZZMMMMM8..:.O:..MMMMMMZIZIOM              \n             M+IZOZM:OOOOMM.....M:8888:MZIZZ+M              \n             M7OZOZ: $$O?M.......  O8$ MZZZZ7M              \n             M++ZZIO M??$M....... O$$O :ZZZ++I              \n             M77++ZZ...................ZZO+:7I             M\n            MM7777ZZOO:.............:OOZZ+777IM         MMMM\n            MII:::7ZZZO:::::::::::::OZIZ77:7ZIM       MMMMMM\n            MII:7:7ZIZNOOO::::::::OONZIZ7777ZIM     MMMMM   \n            MII::::IZ$$I~~~IM8M8~~~ $$ZZ:::7ZIM   MMMMM     \n            IIZ::::Z$$$III 88~8M  I $$$N:::7ZIIMMMMMM       \n           MII77:::$$$$I~   I~~8 M~ $$$$::::7IIMMMM       77\n          MIII7777:NOOOO   8I~~I   OOOOO::7:7ZIIMM      77::\n         MIIIZ::7::ZNONN  8I~~~ 8  NNNNI::77:IIIIM    77::77\n        MIIIZZ7:::7Z$$N$ ~ ~~N~I ~ ON$$Z77::77IIIIM 77::77::\n      MMIIIZZ7::::7Z$N NNNN~N~N~NNZO ~$N77::::IIIIIIM:77::::\n     MIIIIZZI::::7ZZON NNZZN   NNNNN ~ONZ::::7ZIIIIIIM::::::\n     MIIZIII77:7::ZZO~~NNNNNNNNNNONN~NOZZ7:::77IIZIIII::::::\n     MIIIIZZ::::77OI$NN:O$O$N$NNO$O:NN$IOZ77:::ZIIIZIM::::::\n      MIZZZ7::7::ZZN$$NN$$$$$O$$$$ONN$$$IZ::7:::ZZIIM:::::::\n       MII77:::7ZZ$$$$NZN$$$$$$$$ONNN$$$$ZI::::77ZIM77::::::\n        MOII7:::ZZ$$$$OOONNN$$$$NNO$$$$$$NI7::7IIIM77:::::::\n       MIIIIZIZZNN$$$OO$$$$ONNNO$$$$$$$$OONZIIZIIIIM:::::::7\n        MIZIZZIINN$$$O$$$$O$$$$$$$O$$$$$$NNIZZZZZIMM77:::77:\n        IMIOIIZZ$ONNNN$O$$$$$$$$$$OO$$NNNO$ZZIIOIMII:::77::O\n      IIIMIIZZMM$$OOOONNN$$$$$$$$$NNNNOOOO$MMMZIIMIII77:OOOZ\n      IIIMIMIMNN$$OO$$$$ONNZNNNNNO$OOOOO$OO$ZMIMIMIIIIOOZZII\n      IIIIIMMMZNN$OOO$$$$$O$OO$$$$$$OOOOOOONNMMMIIIIIIZIIIII\n      IIIIIIIIIMNNZZO$$$$OOOO$$$$$$$OOOONNZMMMIIIIIIIIIIIIII\n        IIIIIIIIMMZNNNNO$ONN$$$$$$$NNNNMNNMIIIIIIIIIIIIIIIII\n           IIIIIIIIIIMNNZNMMNNNNZZNMMMMIIIIIIIIIOZIIIIIIIIII\n               IIIIIIIIIIIIIMZMMMMMIIIIIIIII::OZIIIIIIIIIIII\n                         IIIIIIIII ~~77::::::OZIIIIIIIIIIIII\n                         MMM       ~7:7:::::OZIIIIIIIIIIIIII\n";
      } else if (command == "dontpanic") {
        lastMessage = "\n                          oooo$$$$$$$$$$$$oooo\n                      oo$$$$$$$$$$$$$$$$$$$$$$$$o\n                   oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$\n   o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$\noo $ $ \"$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$\n\"$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$\n  $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$\n  $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  \"\"\"$$$\n   \"$$$\"\"\"\"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$\n    $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$o\n   o$$\"   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o\n   $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\" \"$$$$$$ooooo$$$$o\n  o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$\n  $$$$$$$$\"$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$\"\"\"\"\"\"\"\"\n \"\"\"\"       $$$$    \"$$$$$$$$$$$$$$$$$$$$$$$$$$$$\"      o$$$\n            \"$$$o     \"\"\"$$$$$$$$$$$$$$$$$$\"$$\"         $$$\n              $$$o          \"$$\"\"$$$$$$\"\"\"\"           o$$$\n               $$$$o                                o$$$\"\n                \"$$$$o      o$$$$$$o\"$$$$o        o$$$$\n                  \"$$$$$oo     \"\"$$$$o$$$$$o   o$$$$\"\"\n                     \"\"$$$$$oooo  \"$$$o$$$$$$$$$\"\"\"\n                        \"\"$$$$$$$oo $$$$$$$$$$\n                                \"\"\"\"$$$$$$$$$$$\n                                    $$$$$$$$$$$$\n                                     $$$$$$$$$$\"\n                                      \"$$$\"\"\"\"\n";
      } else if (command == "cassie") {
        lastMessage = "She's my little fluffy one! My fluffy one that makes my mouth go yum! She's my coosh... coosh? Coosh! Coosh is a sexy bitch!";
      } else if (command == "dragon") {
        lastMessage = "\n                              __________________\n                  __..---..-''_.............,_..`>\n           _..-'':::_:-'_..-'_.-':::::::::,''//||                      _./\n         ,':::::::,'_.-':','.-':.:.::::,','.//:||           _..---.._,','\n       ,':::::::,',':'',',:':'`:.:::,',':`:/'.:::         ,'  ,'    _`/\n      /::.::.::/,':'  ',':' . ' ::,',':'  '   `:\\\\       /     .,' _`:)\n     /:.::.::://'   .          ',','         .   \\\\    ,/    .:;  (::. \\\n    :.::.::._//             .  /'   .     .       `:,./)    (:/ `. \\`:)/\n    |.:._.-'::     _..--.._                  __    (:.)      )    `'  `\n    |.,'    ||  _.'     ,',`.  _.-''``.   ,''  )   /`'      :\n    |/      ||,'    _.-','  |,'        ),'   ,:   (         ; __\n            |/   _,':     / `         '      `:.            \\',.\n              _,':'    : :.                     '    ,'     /'`''\n            ,':'        \\::  /:..        .        .:' (:   `.      _\n          ,':'            \\:::::.    .`.  )   _..:.:,::`.._  ``--'',`\n         /:'      _..-''```::(:.      ::\\/:::.::::.'_:::'  ``----''`'\n        /:     ,-'          `\\:.       `::_::-''\n       ::'    ,               \\:.        |::|\n       |:    :          ,.     `:.       |::|\n       ::.   :        ,'/        `.      ;::;\n        \\:.   `..__.-','           )  .:/:,'\n         `.:.       ,'         _..' _.-::/\n           ``-----''          `:. .'<:::<\n                                `. `._>::`-..__\n                                ,',`-._)_).---'`-._\n                               ,`-`:::`'`\\::'      \\\n                           ___/::::::::,' `:\\      (_\n                       __,'::::`--.._:/     \\`._   (:::._\n                     ,:`._`----..._:::`-._   \\:::.  `-.SSt:.\n";
      } else if (command == "tigger") {
        lastMessage = "\n                                   _.- -.- -._     ..\n                              .;;\"  .oe$$$eeu.. ,?;UU.\n   This one's for you,     ,+'!!  e$$$$$$$R$$$$x ?xd$)\n       Tanya. <3         ,'  !~ u$$$$F,$$$by,?$\"e $F\"        _ -\n               .,;,.   ,dm  :! $$$$$$d( )$( )?d$F       _ -       _\n              !?????X!!!!~!!!X!.\"?????$$$F'.:::::::   -   .  - ~\n              +$$$$$m@`!!   ~? `!kCCU$$$$ ::::::::: g~  ~ -  _\n               \"$BeCeW$:`~..__~x W$$$$$$$e `:::::'.$F           ~\n                 \"****\"      ,``~~?$:=$$$$$$epppe$F`\n                         , '   ,    ?W.\"\"??$$FFF\" *.\n                       '     .     . ?$$e. ==+* ..$f\n                    '     . '      H!.?$$$$$$$$$$$f\n                       . '        !!!! ?$$$$$$$$$$\n                              . ~!!!!!? ?$$$$$$$f.\n                          . '     !!!!~*..****C.-!:..\n                   . -  ~!!!:.    ?!!~.$$$$$$$$$$.!!!!:` .\n              .- ~!::.    !!!!!.  ?X e$$$$$$$$$$$$.`!!!   .! - _\n          . `~!?: ~!!!!!  !!!!!!!!! $$$$$$$$$$$$$$$  !!   !!     !?\n         '      !!:!!!!!!!!!!!!!!!`:$$$$$$$$$$$$$$$U ~ :!!!!    !!~ `\n      .:::::...  !!!!!!!!~~~~!!!!X $$$$$$$$$$$$$$$$$  !!!!!...:<~`   `\n     +   ~~!!!!!!!!~~     ::!!!!!\":$$$$$$$$$$$$$$$$$~ *~~!!!!*`     .:!\n    ::::::::!!!!          \"`~~!!~ *\"\"$$$$$$$$$$$$$$$~       !!!!!!!!!``\n   ,\"`~~!!!!!!~           :        u$$$$$$$$$$$$$$$$~       !!!!``\"   ;\n  . .... ~!!!             .   ..+ $$$$$$$$$$$$$$$$$$~      .!!!!!!?:::-\n  !!!!!!!!!!!!::::+       !!~~~~~ **\"\"$$$$$$$$$$$$$*    .+!!!!!!!!(  ,\n ;!!!!!!!!!!!!!!!~        !!!::.. ue$$$$$$$$$$$$$$$~ !!!!!!!!!!!!!!!!\n !!!!!!!!!!!``            ~!!!!!! $$$$$$$$$$$$$$$$$     !!!!!!!!!!!!\n !!!!!!!!!!!             .   `~~! $$$$$$$$$$$$$$$$`    :!!!!!!!!!!X`\n ~!!!!!!!!!!             ....::!! $$$$$$$$$$$$$$$$     !!!!!!!!!!~\n  `~!!!!!!!!             !!!!!!!!m$$$$$$$$$$$$$$$      !!!!!!!*`\n    `*~X!~*              !!!!!!!*:$$$$$$$$$$$$$$~      ``((`\n                       :!!::   ` \"?I$$$$$$$$$$$`\n                       `~!!!!!- e$$$$$$$$$$$$$~\n                    '     `*~! $$$$$$$$$$$$$$\" .\n                 .:!:.     .: e$$$$$$$$$$$$$\" ~  `\n               '    `~!!!!!!~:$$$$$$$$$$$$* :*    :!       ......\n            ::::::..   ~!!!` $$$$$$$$$$$$\":!~  :!!` `  .!!!!!!!!!!\n           -~!!!!!!!!::..!! 8$$$$$$$$$$*.!!!..!!~ ..- :!!!!!!!~!!!~\n         '     \"~~!!!!!!!!! #$$$$$$$$*(!!!!!!!!!.+!~ :!!!!!~`- -`!\n       ;            `!!!!!!!.\"*$$**\" `````\"`!!!!!!! !!!!!~\n                 ..  .!!!!!~~`               `!!!!`:!!!`        '\n       `.:!!!!!!!!!!!!!!~:                     !!!!!!!~       '\n        ~!!!!!!!~~`~!!!!!!:::                  ~!!!!!!      '\n                 .:!!!!!!!!!!!!:                `!!!!!_  '\n               :::::::!?!!!!!!!!!\n            :!!!!!!!!!!!!!!!!!!~\n            `~!!!!!!!!!!!!!~~\n";
      } else if (command == "mario") {
        lastMessage = "\nS U P E R                             \\| /\nM A R I O           ....'''.           |/\n B R O S     .''''''        '.       \\ |\n             '.     ..     ..''''.    \\| /\nAMC           '...''  '..''     .'     |/\n 2   .sSSs.             '..   ..'    \\ |\n 0  .P'  `Y.               '''        \\| /\n 0  SS    SS                           |/\n 0  SS    SS                           |\n    SS  .sSSs.                       .===.\n    SS .P'  `Y.                      | ? |\n    SS SS    SS                      `==='\n    SS \"\"    SS\n    P.sSSs.  SS\n    .P'  `Y. SS\n    SS    SS SS                 .===..===..===..===.\n    SS    SS SS                 |   || ? ||   ||   |\n    \"\"    SS SS            .===.`==='`==='`==='`==='\n  .sSSs.  SS SS            |   |\n .P'  `Y. SS SS       .===.`==='\n SS    SS SS SS       |   |\n SS    SS SS SS       `==='\nSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n";
      } else if (command == "sexysexy") {
        lastMessage = "\nZZZZZZZZZZOZODZ$777=+I?ZO8ZODMMMMMMMMMMMNND$7?=====7==8~=+.7\nZ$ZZZZZZZZZZZ88$7I~+??ZO$I$DMMN8ZZ$ZODDNMNNDDO++==.I++O~==??\nZZ$$ZZZZZZZZOON$?+=I=77+??8ND$?~:,,,~+I$ONNNNNDI++I??+8~==?+\nZZ$ZZZZZZZZZOOD+=~=.+I:~+O8D7=......,:~=?7NMMMN$I+O???8~=+++\nZZZZZZZZZOZOOOI+=~.+I,==ZZ87=.......,:~~=+7NMMMNI+D+??8=~?++\nZZZZZZZZZZZOO$Z:.,.+,==ZIOZ=........,:~~=+I$NNMMI+D???8==O??\nZ$ZZZZZZZOOOZO=,:,+=?~$7IO?,........,:~==+?78MMM7+OZ??8==77+\nZZZZZZZOZOOOZ+=:+I??~IIO77:.........::~=+?I7ZMMM7+==+?8=====\nZZZZZZZOZOOZ8~~+?II+?777Z=.........,:~~=+??7$MMM7++=+?O=+===\nZZZZZZZOOOO87I?8O77$O?O$$,........,,::~~++?I$MMM$++++?O=++++\n7ZZOOOOOOO8ZII$OZ8ZO?Z$Z+,:=?7I+~:::~:~=+?I77MMMNDD888OOO8OO\n7OOOOOOOO88ZI$DZ8ODO788O=,,.,:=?7I?=:~=+IZDNMMMMMD8888888OO8\n$$88888888O$$8NO8DN7ONO?~:+ZZOZ7\?\?=::~?7Z7II7DMMM8O8DNDDDOOD\nZ$88D8D8DD8ZO88D8MION8NDM8778D$$7+:+.:IODNNNNMMMMO8D8DDD8OOO\nDZODDDDDDD8D88N8NNONDZI==?===?I7+:.,MDMMZZZOZMM8ZM8D88D888O8\nMZZDDDDDDDD88DDNMDDM8I+,.O:~====:,,~..=M7$7I7MNZMD8DD88888OO\nMDZDDDDDDNDO8N8MNDNMZI=....,:=+I?+=...~$N$II78ZMM8O88O$$$$ZZ\nMMOODDDDDDDO8DNMNNMMZ?:.....,~~~~:....,77III7OMMMN7OO7$I77Z$\nMMDODDD8DDDD8DNMMNMM$I:....,~=?I,.....,?$7II7MMMMM$ZI777IZOZ\nMMMOODDDDDDDNNMMNNMMZI~...:=?I?=~~,,,:~I$Z$7$MMMNM8O$I77$Z$Z\nMMM8ONND8DNDNMMMMNMM8I~,,~?7I?:,..:?$I77$$7$MMMMNN888$+$O7I$\nMMMMOOD8DDNNDNMMMNMMD7=,,~=?N87+==+++7Z87I7MMMMMNM8888+?O8?$\nMMMM8ODD8DNDNNMMMNMMNO+:,,~=,,?:~+I77Z8O77MMMMMMDMO88O+?OO77\nMMMMM8D8NDDNNNMMMMMMMDO=:,,:...,:~=??$O$$MMMMMMMNM888O??8OI7\nMMMMM8ODDDDNMNMMNMNNMD8Z+:,....,:+I777$$MMMMMMMMNND88Z?IOO?7\nMMMMMM8NNNNNNMMMMMNNMM88$$~,...,:~=+?IIOMMMMMMMMND8OO7?O8O77\nMMMMMM88NNNNMNNMMMMMNMNOOZ$$=,..,,:=+?7MMMMMMMMMND8Z7I?88I$$\nMMMMMMMONNDMNNNMMMMMMMMNOZZZ$$7=:=?II$MMMMMMMMMMN8O++II88$$$\nMMMMMMMD8NNNNDMNNNMNMMMNDZ$$Z$777IIIIZDMMMMMMMMMNZ+++IIO~:?O\nMMMMMMMN8NDNDMNNNNMMNMNM8Z7777III????$DNMMMMMMMMN8?++I?.....\nMMMMMMMM88888NNZOMMNDNNM8Z7++??++==++$OOMMMMMMMMMN8?+O$????,\nMMMMMMD8?=+ZDNOONMNNNDNNMZ7+==?+=~::~I$ZMMMMMMMMMND$OOO$?+:+\nMMMMM$?.,,$8DDDMMDDDNONMNMO7+=~==:,.,=?7NMMMMMMMN8ZN88O+:,=+\nNNNDD?=?,.,.,~,7D$ND8ONNMNMD+=:,:~,..:+7OMMMMMMMNM8DNOO+~=~=\nDN8D:~~:~~~~.....,+7OODMMNNNNI:,.,,.,,~+ONMMMMNMMND88O++:~=?\nZDO.......~++=.~++:$OO8MMDDNDNO:,,,,,:~=7NMMMDMMMMD88O~=?$~:\n$Z...........II+++I$IODNM888NNDD?=~:::~=I7NNNNNNNNDO?$~:=8MM\nZ.,:::~~==:...,II?I?I8ONND8ODND8M$+=~~~~IZNMMMMNMD8++I~:~ONM\n+,::::~~=+??+,.~I7::.:ZDNN88ODNNDN$I++=IOZNMMMMMMOO\?\?=,,$$OM\n:,........+77$?,=$~,::?8DDND88DNNDMDZ7IZ888NMNMNNOO7~.,77ZZZ\n.........,:=~7O?=+$:=?=$DNDOND8DNDDN8O$O$?ON8DNMN87+:III$$Z+\n.........,:=?II8?+7?+7++DNDD8NDDNNDDOOOO7$I8ZDMNNDIZ7III7$=+\n.........,:=?777O?O8OOOODNNNDDNN8DND8O+~:$7$O$NDNDOZI?III:~+\n..........:=I77ZZ?D8888O8DDDN8NNN8DZ7+==:+7$ZZD8D8Z7I?I,,:=+\n..........:+I77Z?77$O88O8DDDD8O8OO$Z7===?~I$?DD8DO$7?,..,:=Z\n..........~+I7$77777II?7I$Z?$7$ZZ$Z7?~~~$ZOZ?Z8DOZ=.....:~OD\n..........:+77$$O8O7II?I777==+?7I777??$$$OO$$ZOD+~:....,=ZZM\n..........~+I77OZ7O88O$7I$I~~:,:=?$ZZZ$$7I7Z88D?=:,,.,I$ZZ$M\n..........~+I77ZN,=$O8888O8OZZ77II7I7777I7++ZDZI~::?77$Z7+ZM\n..........~+I777MI,:=IOOOOOZZZ$$77777I7?,,,:~7~$?$$7$$7==+ZN\n..........~+I777MNI?:~+$OOOOZZ$7$777+....,:~:+IIZ77$7=~==$O$\n";
      } else if (command == ":v:") {
        lastMessage = "\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMO.,,.,,.,,.,,,,,,,,,OMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMO.,,.,,.,,.,,,,,,,,,OMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMZ.......,,,,,,,,,,,,ZMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMM...............,,,,,,,,,,,,,,,,,,,,,MMMMMMMMMMMM\nMMMMMMMMMMMM...............,,,,,,,,,,,,,,,,,,,,,MMMMMMMMMMMM\nMMMMMMMO.......,,,,,,,,,,,,,,,,+MMMMMMM+,,,,,,,::::OMMMMMMMM\nMMMMMMMO.......,,,,,,,,,,,,,,,,+MMMMMMM+,,,,,,,::::OMMMMMMMM\nMMMMMMMO,,,,,,,,,,,,,,,,,,,,,,,+MMMMMMM?,,,,,,,,:::OMMMMMMMM\nMMMMMMMO,,,,,,,,,,,,,,,,,,,,,,,+MMMMMMM?,,,::::::::~~~~IMMMM\nMMMMMMMO,,,,,,,,,,,,,,,,,,,,,,,+MMMMMMM?,,,::::::::~~~~IMMMM\nMMM+,,,,,,,,,,,OMMMMMMMM,,,,,,,,,,,:::::::::~~~:MMMMMMMMMMMM\nMMM+,,,,,,,,,,,OMMMMMMMM,,,,,,,,,,,:::::::::~~~:MMMMMMMMMMMM\nMMM+,,,,,,,,,,,OMMMMMMMM,,,,,,,,,,,:::::::::~~~:MMMMMMMMMMMM\nMMM+,,,,,,,,,,,OMMMMMMMM,,,::::::::::::OMMMMMMMMMMMMMMMMMMMM\nMMM+,,,,,,,,,,,OMMMMMMMM,,,::::::::::::OMMMMMMMMMMMMMMMMMMMM\nMMM?,,,,,,,,,,,,::::,,,::::::::?MMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?,,,,,,,,,,,,,,,::::::::::::?MMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?,,,,,,,,,,,,:::::::::::::::?MMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?,,,::::::::::::::::,MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?,,,::::::::::::::::,MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?:::::::::::OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?:::::::::::OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMM?:::::::::::OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMM8~~~~:::::::~====MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMM8~~~~:::::::~====MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMM8~~~~============++++++++====MMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMM8~~~~========================MMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMM8~~~~========================MMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMM===================++++++++++++++++=MMMMMMMMMMMM\nMMMMMMMMMMMM===================++++++++++++++++=MMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMM8+++++++++++++++++++++++$MMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMM8+++++++++++++++++++++++7MMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMM8+++++++++++++++++++++++7MMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n";
      } else if (command.substr(0,3) == "log") {
        std::ofstream logfile("codesmineslog.txt");
        if (!logfile) {
          lastMessage = "Error creating 'codesmineslog.txt' log file. Logging failed.";
        } else {
          logfile << command << '\n';
          Redraw(logfile);
        }
        logfile.close();
        lastMessage = "Log saved in codemineslog.txt";
      } else try {
        command.erase(
          std::remove_if(
            &command[0], &command[0] + command.length(),
            IsSpaceOrComma
          ) - &command[0]
        );

        if (command.substr(0, 8) == "setmines") {
          engine.ResetGame(logical_cast<int>(command.substr(8)));
          engine.StopTimer();
          lastMessage = "Number of mines successfully changed.";
        } else if (command == "xyzzy") {
          userIsCheating = !userIsCheating;
          lastMessage = (userIsCheating ?
            "So, you're a cheater? Fine. Be that way. </3" :
            "Had enough cheating? Good! I salute you, desu~!");
        } else if (command == "yzzyx") {
          if (!userIsCheating) {
            lastMessage = "I... can't believe you. Cheater. Blegh.";
            userIsCheating = 2;
          } else {
            lastMessage = "Good. You turned it off. But you're still a cheater. Cheater.";
            userIsCheating = false;
          }
        } else if (engine == GameEngine::Playing) {
           try {
            int row = 0;
            char col = 0;
            if (command.substr(0,4) == "mark" || command.substr(0,4) == "flag") {
              GetTile(command, row, col, 4);
              switch (engine.Mark(row - 1, col - 'a')) {
                case Tile::Flag: {
                  lastMessage = "Tile \"" + command.substr(4) + "\" flagged as a mine.";
                } break;
                case Tile::Unknown: {
                  lastMessage = "Tile \"" + command.substr(4) + "\" is now marked as unknown.";
                } break;
                case Tile::Convex: {
                  lastMessage = "Tile \"" + command.substr(4) + "\" is now marked as not a mine.";
                } break;
                default: {
                  lastMessage = "Uh, you already cleared that tile; why are you trying to flag it?";
                } break;
              }
            } else {
              GetTile(command, row, col, 0);
              try {
                engine.Activate(row - 1, col - 'a');
                lastMessage = "Tile \"" + command + "\" safely activated.";
              }
              catch (Tile::Error& error) {
                if (error == Tile::AlreadyActivated) {
                  lastMessage = "Error: Tile \"" + command + "\" was already activated.";
                } else if (error == Tile::AlreadyFlagged) {
                  lastMessage = "Error: Tile \"" + command + "\" was already flagged as a mine.";
                } else throw;
              }
              catch (...) {
                throw;
              }
            }
          }
          catch (GameEngine::Bounds& error) {
            lastMessage = std::string("Error: ") + error.what();
          }
          catch (...) {
            throw;
          }
        }
        if (engine == GameEngine::Dead) {
          std::time_t duration = engine.StopTimer();
          lastMessage = "YOU HAVE DIED (after "
            + logical_cast<std::string>(duration)
            + Plural(duration, "second")
            + "). Type \"restart\" to try again.";
          engine.StopTimer();
        } else if (engine == GameEngine::Completed) {
          std::time_t duration = engine.StopTimer();
          if (userIsCheating) {
            lastMessage = "You cheated to win in "
              + logical_cast<std::string>(duration)
              + Plural(duration, "second")
              + " Type \"restart\" to try again. (Cheat deactivated, by the way)";
            userIsCheating = false;
          } else {
            lastMessage = "You have won in "
              + logical_cast<std::string>(duration)
              + Plural(duration, "second")
              + "! Type \"restart\" to try again.";
          }
        } else continue;
      }
      catch (std::bad_cast&) {
        lastMessage = "Invalid input detected; please re-enter the input correctly.";
      }
      catch (GameEngine::NumMines& error) {
        lastMessage = std::string("Error: ") + error.what();
      }
      catch (std::exception& error) {
        lastMessage = error.what();
      }
      catch (...) {
        lastMessage = "Unknown error detected. You did something bad, desu~";
        throw;
      }
    }
  }
  
  void InputOutput::PauseForInput() {
    if (input) {
      input->get();
      input->clear();
    }
  }
  
  std::string InputOutput::GetCommand() {
    std::string command;
    if (input) {
      input->clear();
      std::getline(*input, command);
    }
    return command;
  }
  
  void InputOutput::Redraw() {
    Redraw(output);
  }
  
  void InputOutput::Redraw(std::ostream& out) {
    const std::vector<std::vector<Tile> >& matrix = engine.GetTileMatrix();
    std::string lsmiley;
    std::string rsmiley;
    if (engine == GameEngine::Dead) {
      lsmiley = "x(";
      rsmiley = ")x";
    } else if (engine == GameEngine::Completed) {
      lsmiley = "8)";
      rsmiley = "(8";
    } else {
      lsmiley = "=)";
      rsmiley = "(=";
    }
    const char* rightSideBar[20] = {
      "| 1|                   |\n",
      "| 2| To select a tile, |\n",
      "| 3| enter the row     |\n",
      "| 4| number then the   |\n",
      "| 5| column letter.    |\n",
      "| 6|  >> 10A           |\n",
      "| 7|  >> 10 A          |\n",
      "| 8|  >> 10,A          |\n",
      "| 9| As always, case   |\n",
      "|10| does not matter;  |\n",
      "|11| both 'a' and 'A'  |\n",
      "|12| work fine.        |\n",
      "|13|                   |\n",
      "|14|  Other Commands:  |\n",
      "|15|                   |\n",
      "|16| FLAG tile         |\n",
      "|17| SETMINES #        |\n",
      "|18| RESTART           |\n",
      "|19| QUIT              |\n",
      "|20|                   |\n"
    };
    const char* leftSideBar[20] = {
      "| 1|", "| 2|", "| 3|", "| 4|",
      "| 5|", "| 6|", "| 7|", "| 8|",
      "| 9|", "|10|", "|11|", "|12|",
      "|13|", "|14|", "|15|", "|16|",
      "|17|", "|18|", "|19|", "|20|"
    };
    const char* horizBar = "|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|";
    out <<
"+-----------------------------------------------------------------------------+\n" <<
"|                                   CodeMines                                 |\n" <<
"|                                By Peter Schultz                             |\n" <<
"+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-------------------+\n" <<
"|" << lsmiley << horizBar << rsmiley << "|     Commands:     |\n";
    for (unsigned int i = 0; i < matrix.size(); ++i) {
      out << leftSideBar[i];
      for (unsigned int j = 0; j < matrix[i].size(); ++j) {
        if (j == 0) {
          // noop
        } else if (!IsConvexTile(matrix[i][j]) || matrix[i][j] == Tile::Flag) {
          out << ' ';
        } else if (!IsConvexTile(matrix[i][j-1]) || matrix[i][j-1] == Tile::Flag) {
          out << ' ';
        } else {
          out << '|';
        }
        if (userIsCheating == 2 && (Tile::State(matrix[i][j]) == Tile::Volatile)) {
          out << '0';
        } else out << char(Tile::Character(matrix[i][j]));
      }
      out << rightSideBar[i];
    }
    out <<
"|" << lsmiley << horizBar << rsmiley << "|    Mines: " << std::setw(3) <<
       std::left << engine.Mines() << std::right << std::setw(7) << "|\n" <<
"+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-------------------+\n" <<
"| {{ " << lastMessage << " }} " << std::setw(71 - lastMessage.size()) << " |\n" <<
"+ >> " << std::flush;
  }
  
  void InputOutput::GetTile(std::string& command, int& row, char& col, std::size_t start) {
    engine.StartTimer();
    if (command[start] <= 'z' && command[start] >= 'a') {
      col = command[start];
      row = logical_cast<int>(command.substr(start + 1));
    } else if (logical_cast<int>(command.substr(start,1)) > 0) {
      try {
        if (logical_cast<int>(command.substr(start,2)) >= 0) {
          row = logical_cast<int>(command.substr(start,2));
        }
      }
      catch (...) {
        if (logical_cast<int>(command.substr(start,1)) > 0) {
          row = logical_cast<int>(command.substr(start,1));
        }
      }
      if (command[start + (row < 10 ? 1 : 2)] <= 'z' && command[start + (row < 10 ? 1 : 2)] >= 'a') {
        col = command[start + (row < 10 ? 1 : 2)];
      } else throw std::bad_cast();
    } else throw std::bad_cast();
  }
  
}
