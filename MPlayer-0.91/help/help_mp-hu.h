// Translated by: Gabucino the Almighty! <gabucino@mplayerhq.hu>
// Send me money/hw/babes!
// ... Okay enough of the hw, now send the other two!

// In synch with rev 1.95

// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char help_text[]=
"Ind�t�s:   mplayer [opci�k] [url|�tvonal/]filen�v\n"
"\n"
"Alapvet� opci�k: (az �sszes opci� list�j�hoz l�sd a man lapot!)\n"
" -vo <drv[:dev]> videomeghajt� �s -alegys�g kiv�laszt�sa (lista: '-vo help')\n"
" -ao <drv[:dev]> audiomeghajt� �s -alegys�g kiv�laszt�sa (lista: '-ao help')\n"
#ifdef HAVE_VCD
" -vcd <s�vsz�m>  lej�tsz�s VCD (video cd)-s�vb�l, k�zvetlen�l az eszk�zr�l\n"
#endif
#ifdef HAVE_LIBCSS
" -dvdauth <megh> DVD-meghajt� el�r�si �tj�nak megad�sa (k�dolt lemezekhez)\n"
#endif
#ifdef USE_DVDREAD
" -dvd <titleno>  a megadott DVD s�v lej�tsz�sa, file helyett\n"
" -alang/-slang   DVD audio/felirat nyelv kiv�laszt�sa (2 bet�s orsz�gk�ddal)\n"
#endif
" -ss <id�poz>    a megadott (m�sodperc v. �ra:perc:mperc) poz�ci�ra teker�s\n"
" -nosound        hanglej�tsz�s kikapcsol�sa\n"
" -fs -vm -zoom   teljesk�perny�s lej�tsz�s opci�i (teljk�p,m�dv�lt,szoft.nagy)\n"
" -x <x> -y <y>   lej�tsz�si ablak felbont�s�nak fel�lb�r�lata (m�dv�lt�shoz vagy szoftveres nagy�t�shoz)\n"
" -sub <file>     felhaszn�land� felirat-file megad�sa (l�sd -subfps, -subdelay)\n"
" -playlist <file> lej�tsz�si lista file megad�sa\n"
" -vid x -aid y   lej�tszand� video- (x) �s audio- (y) stream-ek kiv�laszt�sa\n"
" -fps x -srate y video (x k�pkocka/mp) �s audio (y Hz) r�ta megad�sa\n"
" -pp <min�s�g>   k�pjav�t�s fokozatainak be�ll�t�sa (l�sd a man lapot)\n"
" -framedrop      k�pkock�k eldob�s�nak enged�lyez�se (lass� g�pekhez)\n"
"\n"
"Legfontosabb billenty�k: (a teljes list�hoz l�sd a man lapot, �s az input.conf file-t)\n"
" <-  vagy  ->    10 m�sodperces h�tra/el�re ugr�s\n"
" fel vagy le     1 percnyi h�tra/el�re ugr�s\n"
" pgup v. pgdown  10 percnyi h�tra/el�re ugr�s\n"
" < vagy >        1 file-al el�re/h�tra l�p�s a lej�tsz�si list�ban\n"
" p vagy SPACE    pillanat�llj (b�rmely billenty�re tov�bbmegy)\n"
" q vagy ESC      kil�p�s\n"
" + vagy -        audio k�sleltet�se +/- 0.1 m�sodperccel\n"
" o               OSD-m�d v�lt�sa:  nincs / keres�s�v / keres�s�v+id�\n"
" * vagy /        hanger� fel/le\n"
" z vagy x        felirat k�sleltet�se +/- 0.1 m�sodperccel\n"
" r vagy t        felirat poz�ci�j�nak megv�ltoztat�sa, l�sd -vop expand-ot is!\n"
"\n"
" * * * A MANPAGE TOV�BBI R�SZLETEKET, OPCI�KAT, BILLENTY�KET TARTALMAZ ! * * *\n"
"\n";
#endif

// ========================= MPlayer messages ===========================

// mplayer.c: 

#define MSGTR_Exiting "\nKil�pek... (%s)\n"
#define MSGTR_Exit_quit "Kil�p�s"
#define MSGTR_Exit_eof "V�ge a file-nak"
#define MSGTR_Exit_error "V�gzetes hiba"
#define MSGTR_IntBySignal "\nAz MPlayer fut�sa %d-es szign�l miatt megszakadt a %s modulban\n"
#define MSGTR_NoHomeDir "Nem tal�lom a HOME konyvt�rat\n"
#define MSGTR_GetpathProblem "get_path(\"config\") probl�ma\n"
#define MSGTR_CreatingCfgFile "Konfigur�ci�s file l�trehoz�sa: %s\n"
#define MSGTR_InvalidVOdriver "Nem l�tez� video meghajt�: %s\nHaszn�ld a '-vo help' opci�t, hogy list�t kapj a haszn�lhat� vo meghajt�kr�l.\n"
#define MSGTR_InvalidAOdriver "Nem l�tez� audio meghajt�: %s\nHaszn�ld az '-ao help' opci�t, hogy list�t kapj a haszn�lhat� ao meghajt�kr�l.\n"
#define MSGTR_CopyCodecsConf "(m�sold/linkeld az etc/codecs.conf file-t ~/.mplayer/codecs.conf-ba)\n"
#define MSGTR_BuiltinCodecsConf "Beford�tott codecs.conf - ot haszn�lom.\n"
#define MSGTR_CantLoadFont "Nem tudom bet�lteni a k�vetkez� fontot: %s\n"
#define MSGTR_CantLoadSub "Nem tudom bet�lteni a feliratot: %s\n"
#define MSGTR_ErrorDVDkey "Hiba a DVD-KULCS feldolgoz�sa k�zben.\n"
#define MSGTR_CmdlineDVDkey "A parancssorban megadott DVD-kulcs tov�bbi dek�dol�s c�lj�b�l elt�rol�sra ker�lt.\n"
#define MSGTR_DVDauthOk "DVD-autentik�ci�s folyamat, �gy t�nik, sikerrel v�gz�d�tt.\n"
#define MSGTR_DumpSelectedStreamMissing "dump: V�GZETES HIBA: a k�rt stream nem tal�lhat�!\n"
#define MSGTR_CantOpenDumpfile "Nem tudom megnyitni a dump file-t!\n"
#define MSGTR_CoreDumped "Kinyomattam a cuccost, j�l.\n"
#define MSGTR_FPSnotspecified "Az FPS (k�pkocka/mp) �rt�k nincs megadva, vagy hib�s! Haszn�ld az -fps opci�t!\n"
#define MSGTR_TryForceAudioFmtStr "Megpr�b�lom a(z) %s audio codec-csal�dot haszn�lni ...\n"
#define MSGTR_CantFindAfmtFallback "A megadott audio codec-csal�dban nem tal�ltam ideval� meghajt�t, pr�b�lkozok m�s meghajt�val.\n"
#define MSGTR_CantFindAudioCodec "Nem tal�lok codecet a(z) 0x%X audio-form�tumhoz !\n"
#define MSGTR_TryUpgradeCodecsConfOrRTFM "*** Friss�tsd a %s-t az etc/codecs.conf-b�l\n*** Ha m�g mindig nem j�, olvasd el a DOCS/codecs.html-t!\n"
#define MSGTR_CouldntInitAudioCodec "Nem tudom ind�tani az audio codecet! -> nincshang ;)\n"
#define MSGTR_TryForceVideoFmtStr "Megpr�b�lom a(z) %s video codec-csal�dot haszn�lni ...\n"
#define MSGTR_CantFindVideoCodec "Nem tal�lok codec-et ami megfelel a kivalasztott vo-hoz es 0x%X video-form�tumhoz !\n"
#define MSGTR_VOincompCodec "A kiv�lasztott video_out meghajt� inkompatibilis ezzel a codec-kel.\n"
#define MSGTR_CannotInitVO "V�GZETES HIBA: Nem tudom elind�tani a video-meghajt�t!\n"
#define MSGTR_CannotInitAO "nem tudom megnyitni az audio-egys�get -> NOSOUND\n"
#define MSGTR_StartPlaying "Lej�tsz�s ind�t�sa...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"         ***************************************\n"\
"         **** A rendszered t�l LASS� ehhez! ****\n"\
"         ***************************************\n"\
"Lehets�ges okok, �s megold�saik:\n"\
"- Legyakrabban : hib�s _audio_ meghajt�\n"\
"  - Pr�b�ld ki az -ao sdl opci�t, vagy haszn�ld az ALSA 0.9 OSS emul�ci�j�t.\n"\
"  - Adj k�l�nb�z� �rt�keket az -autosync opci�nak, kezdetnek a 30 megteszi.\n"\
"- Lass� videokimenet\n"\
"  - Egy m�sik -vo meghajt� kipr�b�l�sa eredm�nyre vezethet (a list�hoz l�sd\n"\
"    -vo help), �s/vagy haszn�ld a -framedrop opci�t!\n"\
"- Lass� CPU\n"\
"  - Nagy felbont�s� DivX/DVD lej�tsz�s�val nem �rdemes gyenge processzoron\n"\
"    pr�b�lkozni! Esetleg -hardframedrop ?\n"\
"- Hib�s file\n"\
"  - A -nobps -ni -forceidx -mc opci�k kombin�ci�val �rdemes sz�rakozni.\n"\
"- Lass� m�dia (NFS/SMB, DVD, VCD, stb)\n"\
"  - Pr�b�ld ki a -cache 8192 opci�t.\n"\
"- Tal�n egy non-interleaved AVI filet pr�b�lsz -cache opci�val lej�tszani?\n"\
"  - Haszn�ld a -nocache opci�t.\n"\
"Tuninghoz tippeket a DOCS/video.html �s DOCS/sound.html file-ok tartalmaznak.\n"\
"Ha ezek ut�n sem tetszik az eredm�ny, olvasd el a DOCS/bugreports.html file-t.\n\n"

#define MSGTR_NoGui "Az MPlayer grafikus fel�let N�LK�L lett ford�tva!\n"
#define MSGTR_GuiNeedsX "Az MPlayer grafikus fel�let�nek X11-re van sz�ks�ge!\n"
#define MSGTR_Playing "%s lej�tsz�sa\n"
#define MSGTR_NoSound "Audio: nincs hang!!!\n"
#define MSGTR_FPSforced "FPS k�nyszer�tve %5.3f  (ftime: %5.3f)\n"
#define MSGTR_CompiledWithRuntimeDetection "Fut�sidej� CPU Detekt�l�s haszn�lata - ez nem optim�lis! A legjobb teljes�tm�ny el�r�s�hez ford�tsd �jra az MPlayer-t a --disable-runtime-cpudetection\n opci�val\n"
#define MSGTR_CompiledWithCPUExtensions "x86-os CPU - a k�vetkez� kiterjeszt�sek haszn�lata:"
#define MSGTR_AvailableVideoOutputPlugins "Rendelkez�sre �ll� video pluginek:\n"
#define MSGTR_AvailableVideoOutputDrivers "Rendelkez�sre �ll� video meghajt�k:\n"
#define MSGTR_AvailableAudioOutputDrivers "Rendelkez�sre �ll� audio meghajt�k:\n"
#define MSGTR_AvailableAudioCodecs "Rendelkez�sre �ll� audio codec-ek:\n"
#define MSGTR_AvailableVideoCodecs "Rendelkez�sre �ll� video codec-ek:\n"
#define MSGTR_AvailableAudioFm "\nRendelkez�sre �ll� (beford�tott) audio codec csal�dok/meghajt�k:\n"
#define MSGTR_AvailableVideoFm "\nRendelkez�sre �ll� (beford�tott) video codec csal�dok/meghajt�k:\n"
#define MSGTR_AvailableFsType "A haszn�lhat� teljesk�perny�s r�teg-m�dok:\n"
#define MSGTR_UsingRTCTiming "Linux hardveres RTC id�z�t�s haszn�lata (%ldHz)\n"
#define MSGTR_CannotReadVideoProperties "Video: tulajdons�gok beolvas�sa nem lehets�ges\n"
#define MSGTR_NoStreamFound "Nem tal�lhat� stream\n"
#define MSGTR_InitializingAudioCodec "Audio codec inicializ�l�sa...\n"
#define MSGTR_ErrorInitializingVODevice "Hiba a kiv�lasztott video_out (-vo) egys�g inicializ�sakor!\n"
#define MSGTR_ForcedVideoCodec "K�nyszer�tett video codec: %s\n"
#define MSGTR_ForcedAudioCodec "K�nyszer�tett audio codec: %s\n"
#define MSGTR_AODescription_AOAuthor "AO: Le�r�s: %s\nAO: K�sz�t�: %s\n"
#define MSGTR_AOComment "AO: Komment: %s\n"
#define MSGTR_Video_NoVideo "Video: nincs video!!!\n"
#define MSGTR_NotInitializeVOPorVO "\nHIBA: Nem siker�lt a video filterek (-vop) vagy a video kimenet (-vo) inicializ�l�sa!\n"
#define MSGTR_Paused "\n  =====  SZ�NET  =====\r"
#define MSGTR_PlaylistLoadUnable "\nLej�tsz�si lista (%s) bet�lt�se sikertelen\n"
#define MSGTR_Exit_SIGILL_RTCpuSel \
"- Az MPlayer egy 'illeg�lis utas�t�st' hajtott v�gre.\n"\
"  Lehet hogy a fut�sidej� CPU detekt�l� k�d bugja...\n"\
"  Olvasd el a DOCS/bugreports.html file-t.\n"
#define MSGTR_Exit_SIGILL \
"- Az MPlayer egy 'illeg�lis utas�t�st' hajtott v�gre.\n"\
"  Ez akkor t�rt�nik amikor m�s CPU-n futtatod az MPlayer-t mint amire a\n"\
"  ford�t�s/optimaliz�l�s t�rt�nt.\n  Ellen�rizd!\n"
#define MSGTR_Exit_SIGSEGV_SIGFPE \
"- Az MPlayer r�pke f�lrel�p�se miatt hiba l�pett fel a CPU/FPU/RAM-ban.\n"\
"  Ford�tsd �jra az MPlayer-t az --enable-debug opci�val, �s k�sz�ts egy\n"\
"  'gdb' backtrace-t. A r�szletek a DOCS/bugreports.html file-ban tal�lhat�ak.\n"
#define MSGTR_Exit_SIGCRASH \
"- Az MPlayer elcrashelt. Ennek nem lenne szabad megt�rt�nnie.\n"\
"  Az ok lehet egy hiba az MPlayer k�dj�ban _vagy_ a Te meghajt�idban, _vagy_\n"\
"  a gcc-ben. Ha �gy v�led hogy ez egy MPlayer hiba, �gy olvasd el a\n"\
"  DOCS/bugreports.html file-t. Amig ezt figyelmesen meg nem teszed, nem tudunk\n"\
"  seg�teni.\n"


// mencoder.c:

#define MSGTR_UsingPass3ControllFile "Pass3 file haszn�lata: %s\n"
#define MSGTR_MissingFilename "\nHi�nyz� filen�v!\n\n"
#define MSGTR_CannotOpenFile_Device "File/eszk�z megnyit�sa sikertelen\n"
#define MSGTR_ErrorDVDAuth "Hiba a DVD authentik�ci� k�zben...\n"
#define MSGTR_CannotOpenDemuxer "Demuxer megh�v�sa sikertelen\n"
#define MSGTR_NoAudioEncoderSelected "\nNem v�lasztott�l ki audio enk�dert (-oac)! V�lassz egyet, vagy haszn�ld a -nosound opci�t. L�sd -oac help!\n"
#define MSGTR_NoVideoEncoderSelected "\nNem v�lasztott�l ki video enk�dert (-ovc)! V�lassz egyet, l�sd -ovc help!\n"
#define MSGTR_InitializingAudioCodec "Audio codec inicializ�l�sa...\n"
#define MSGTR_CannotOpenOutputFile "Nem tudom a kimeneti file-t (%s) megnyitni\n"
#define MSGTR_EncoderOpenFailed "Enk�der megh�v�sa sikertelen\n"
#define MSGTR_ForcingOutputFourcc "Kimeneti fourcc k�nyszer�t�se: %x [%.4s]\n"
#define MSGTR_WritingAVIHeader "AVI fejl�c �r�sa...\n"
#define MSGTR_DuplicateFrames "\n%d darab k�pkocka dupl�z�sa!!!     \n"
#define MSGTR_SkipFrame "\nk�pkocka �tugr�sa!!!     \n"
#define MSGTR_ErrorWritingFile "%s: hiba a file �r�s�n�l.\n"
#define MSGTR_WritingAVIIndex "\nAVI index �r�sa...\n"
#define MSGTR_FixupAVIHeader "AVI fejl�c fix�l�sa...\n"
#define MSGTR_RecommendedVideoBitrate "Aj�nlott video bitr�ta %s CD-hez: %d\n"
#define MSGTR_VideoStreamResult "\nVideo stream: %8.3f kbit/mp  (%d bps)  m�ret: %d byte  %5.3f mp  %d k�pkocka\n"
#define MSGTR_AudioStreamResult "\nAudio stream: %8.3f kbit/mp  (%d bps)  m�ret: %d byte  %5.3f mp\n"

// cfg-mencoder.h:

#define MSGTR_MEncoderMP3LameHelp "\n\n"\
" vbr=<0-4>     a v�ltoz� bitr�t�j� enk�dol�s m�dja\n"\
"                0: cbr\n"\
"                1: mt\n"\
"                2: rh(alap�rtelmezett)\n"\
"                3: abr\n"\
"                4: mtrh\n"\
"\n"\
" abr           �tlagos bitr�ta\n"\
"\n"\
" cbr           konstans bitr�ta\n"\
"               Forces also CBR mode encoding on subsequent ABR presets modes\n"\
"\n"\
" br=<0-1024>   bitr�ta kBit-ben (csak CBR �s ABR)\n"\
"\n"\
" q=<0-9>       min�s�g (0-legjobb, 9-legrosszabb) (csak VBR-n�l)\n"\
"\n"\
" aq=<0-9>      algoritmikus min�s�g (0-legjobb, 9-legrosszabb/leggyorsabb)\n"\
"\n"\
" ratio=<1-100> t�m�r�t�s ar�nya\n"\
"\n"\
" vol=<0-10>    audio bemenet hangereje\n"\
"\n"\
" mode=<0-3>    (alap: automatikus)\n"\
"                0: stereo\n"\
"                1: joint-stereo\n"\
"                2: dualchannel\n"\
"                3: mono\n"\
"\n"\
" padding=<0-2>\n"\
"                0: nincs\n"\
"                1: mind\n"\
"                2: �ll�t�s\n"\
"\n"\
" fast          valamivel gyorsabb VBR enk�dol�s, kicsit rosszabb min�s�g �s\n"\
"               magasabb bitr�ta.\n"\
"\n"\
" preset=<�rt�k> el�re be�ll�tott �rt�kek.\n"\
"                 medium: VBR  enk�dol�s,  kellemes min�s�g\n"\
"                 (150-180 kbps bitr�ta tartom�ny)\n"\
"                 standard:  VBR enk�dol�s, j� min�s�g\n"\
"                 (170-210 kbps bitr�ta tartom�ny)\n"\
"                 extreme: VBR enk�dol�s, nagyon j� min�s�g\n"\
"                 (200-240 kbps bitr�ta tartom�ny)\n"\
"                 insane:  CBR  enk�dol�s, legjobb min�s�g\n"\
"                 (320 kbps bitr�ta)\n"\
"                 <8-320>: ABR enk�dol�s �tlagban a megadott bitr�t�val.\n\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "A CD-ROM meghajt� (%s) nem tal�lhat�!\n"
#define MSGTR_ErrTrackSelect "Hiba a VCD-s�v kiv�laszt�sakor!"
#define MSGTR_ReadSTDIN "Olvas�s a szabv�nyos bemenetr�l (stdin)...\n"
#define MSGTR_UnableOpenURL "Nem megnyithat� az URL: %s\n"
#define MSGTR_ConnToServer "Csatlakozom a szerverhez: %s\n"
#define MSGTR_FileNotFound "A file nem tal�lhat�: '%s'\n"

#define MSGTR_SMBInitError "Samba kliens k�nyvt�r nem inicializ�lhat�: %d\n"
#define MSGTR_SMBFileNotFound "Nem nyithat� meg a h�l�zatr�l: '%s'\n"
#define MSGTR_SMBNotCompiled "Nincs beford�tva az MPlayer - be az SMB t�mogat�s\n"

#define MSGTR_CantOpenDVD "Nem tudom megnyitni a DVD eszk�zt: %s\n"
#define MSGTR_DVDwait "A lemez strukt�r�j�nak olvas�sa, k�rlek v�rj...\n"
#define MSGTR_DVDnumTitles "%d s�v van a DVD-n.\n"
#define MSGTR_DVDinvalidTitle "Helytelen DVD s�v: %d\n"
#define MSGTR_DVDnumChapters "Az adott DVD s�vban %d fejezet van.\n"
#define MSGTR_DVDinvalidChapter "Helytelen DVD fejezet: %d\n"
#define MSGTR_DVDnumAngles "%d darab kamera�ll�s van ezen a DVD s�von.\n"
#define MSGTR_DVDinvalidAngle "Helytelen DVD kamera�ll�s: %d\n"
#define MSGTR_DVDnoIFO "Nem tudom a(z) %d. DVD s�vhoz megnyitni az IFO file-t.\n"
#define MSGTR_DVDnoVOBs "Nem tudom megnyitni a s�vot (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDopenOk "DVD sikeresen megnyitva!\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Vigy�zat! T�bbsz�r�sen defini�lt Audio-folyam: %d (Hib�s file?)\n"
#define MSGTR_VideoStreamRedefined "Vigy�zat! T�bbsz�r�sen defini�lt Video-folyam: %d (Hib�s file?)\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: T�l sok (%d db, %d b�jt) audio-csomag a pufferben!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: T�l sok (%d db, %d b�jt) video-csomag a pufferben!\n"
#define MSGTR_MaybeNI "Tal�n ez egy nem �sszef�s�lt (interleaved) file vagy a codec nem m�k�dik j�l?\n" \
		      "AVI file-okn�l pr�b�ld meg a non-interleaved m�d k�nyszer�t�s�t a -ni opci�val.\n"
#define MSGTR_SwitchToNi "\nRosszul �sszef�s�lt (interleaved) file, �tv�lt�s -ni m�dba!\n"
#define MSGTR_Detected_XXX_FileFormat "Ez egy %s form�tum� file!\n"
#define MSGTR_DetectedAudiofile "Audio file detekt�lva!\n"
#define MSGTR_NotSystemStream "Nem MPEG System Stream form�tum... (tal�n Transport Stream?)\n"
#define MSGTR_InvalidMPEGES "Hib�s MPEG-ES-folyam? L�pj kapcsolatba a k�sz�t�kkel, lehet, hogy hiba!\n"
#define MSGTR_FormatNotRecognized "========= Sajnos ez a fileform�tum ismeretlen vagy nem t�mogatott ===========\n"\
				  "= Ha ez egy AVI, ASF vagy MPEG file, l�pj kapcsolatba a k�sz�t�kkel (hiba)! =\n"
#define MSGTR_MissingVideoStream "Nincs k�pfolyam!\n"
#define MSGTR_MissingAudioStream "Nincs hangfolyam... -> hang n�lk�l\n"
#define MSGTR_MissingVideoStreamBug "Nincs k�pfolyam?! �rj a szerz�nek, lehet hogy hiba :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: a file nem tartalmazza a k�rt hang vagy k�p folyamot\n"

#define MSGTR_NI_Forced "K�nyszer�tve"
#define MSGTR_NI_Detected "Detekt�lva"
#define MSGTR_NI_Message "%s NON-INTERLEAVED AVI form�tum!\n"

#define MSGTR_UsingNINI "NON-INTERLEAVED hib�s AVI form�tum haszn�lata!\n"
#define MSGTR_CouldntDetFNo "Nem tudom meghat�rozni a k�pkock�k sz�m�t (abszolut teker�shez)   \n"
#define MSGTR_CantSeekRawAVI "Nem tudok nyers .AVI-kban tekerni! (index kell, pr�b�ld az -idx kapcsol�val!)\n"
#define MSGTR_CantSeekFile "Nem tudok ebben a fileban tekerni!  \n"

#define MSGTR_EncryptedVOB "K�dolt VOB file (libcss t�mogat�s nincs beford�tva!) Olvasd el a doksit\n"
#define MSGTR_EncryptedVOBauth "K�dolt folyam, de nem k�rt�l autentik�l�st!!\n"

#define MSGTR_MOVcomprhdr "MOV: T�m�r�tett fejl�cek (m�g) nincsenek t�mogatva!\n"
#define MSGTR_MOVvariableFourCC "MOV: Vigy�zat! v�ltoz� FOURCC detekt�lva!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Vigy�zat! t�l sok s�v!"
#define MSGTR_FoundAudioStream "==> Megtal�lt audio stream: %d\n"
#define MSGTR_FoundVideoStream "==> Megtal�lt video stream: %d\n"
#define MSGTR_DetectedTV "TV detekt�lva! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "OGG demuxer megh�v�sa nem siker�lt\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: Audio stream keres�se (id:%d)\n"
#define MSGTR_CannotOpenAudioStream "Audio stream megnyit�sa sikertelen: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Felirat stream megnyit�sa sikertelen: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Audio demuxer megh�v�sa sikertelen: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Felirat demuxer megh�v�sa sikertelen: %s\n"
#define MSGTR_TVInputNotSeekable "TV bemenet nem tekerhet�! (Meg k�ne csin�lni hogy most v�ltson csatorn�t ;)\n"
#define MSGTR_DemuxerInfoAlreadyPresent "%s demuxer info m�r jelen van!\n"
#define MSGTR_ClipInfo "Clip info: \n"

#define MSGTR_LeaveTelecineMode "\ndemux_mpg: Progressz�v file, kil�p�s a 3:2 TELECINE m�db�l\n"
#define MSGTR_EnterTelecineMode "\ndemux_mpg: 3:2 TELECINE detekt�lva, inverz telecine fix haszn�lata. Az �j FPS: %5.3f!  \n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "Nem tudom megnyitni a kodeket\n"
#define MSGTR_CantCloseCodec "Nem tudom lez�rni a kodeket\n"

#define MSGTR_MissingDLLcodec "HIBA: Nem tudom megnyitni a k�rt DirectShow kodeket: %s\n"
#define MSGTR_ACMiniterror "Nem tudom bet�lteni/inicializ�lni a Win32/ACM kodeket (hi�nyz� DLL file?)\n"
#define MSGTR_MissingLAVCcodec "Nem tal�lom a(z) '%s' nev� kodeket a libavcodec-ben...\n"

#define MSGTR_MpegNoSequHdr "MPEG: V�GZETES: v�ge lett a filenak mik�zben a szekvencia fejl�cet kerestem\n"
#define MSGTR_CannotReadMpegSequHdr "V�GZETES: Nem tudom olvasni a szekvencia fejl�cet!\n"
#define MSGTR_CannotReadMpegSequHdrEx "V�GZETES: Nem tudom olvasni a szekvencia fejl�c kiterjeszt�s�t!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Hib�s szekvencia fejl�c!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Hib�s szekvencia fejl�c kiterjeszt�s!\n"

#define MSGTR_ShMemAllocFail "Nem tudok megosztott mem�ri�t lefoglalni\n"
#define MSGTR_CantAllocAudioBuf "Nem tudok kimeneti hangbuffer lefoglalni\n"

#define MSGTR_UnknownAudio "Ismeretlen/hi�nyz� hangform�tum, hang kikapcsolva\n"

#define MSGTR_UsingExternalPP "[PP] K�ls� min�s�gjav�t� filter haszn�lata, max min�s�g = %d\n"
#define MSGTR_UsingCodecPP "[PP] Codecbeli min�s�gjav�t�s haszn�lata, max min�s�g = %d\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "'%s' video tulajdons�g nem t�mogatott a kiv�lasztott vo & vd meghajt�k �ltal! \n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "A k�rt [%s] video codec csal�d (vfm=%s) nem kiv�laszthat� (ford�t�sn�l kapcsold be!)\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "A k�rt [%s] audio codec csal�d (afm=%s) nem kiv�laszthat� (ford�t�sn�l kapcsold be!)\n"
#define MSGTR_OpeningVideoDecoder "Video dek�der megh�v�sa: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "Audio dek�der megh�v�sa: [%s] %s\n"
#define MSGTR_UninitVideoStr "uninit video: %s  \n"
#define MSGTR_UninitAudioStr "uninit audio: %s  \n"
#define MSGTR_VDecoderInitFailed "VDecoder init nem siker�lt :(\n"
#define MSGTR_ADecoderInitFailed "ADecoder init nem siker�lt :(\n"
#define MSGTR_ADecoderPreinitFailed "ADecoder preinit nem siker�lt :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: %d byte allok�l�sa bemeneti buffernek\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: %d + %d = %d byte allok�l�sa bemeneti buffernek\n"

// LIRC:
#define MSGTR_SettingUpLIRC "lirc t�mogat�s ind�t�sa...\n"
#define MSGTR_LIRCdisabled "Nem fogod tudni haszn�lni a t�vir�ny�t�t\n"
#define MSGTR_LIRCopenfailed "Nem tudtam megnyitni a lirc t�mogat�st!\n"
#define MSGTR_LIRCcfgerr "Nem tudom olvasni a LIRC konfigur�ci�s file-t : %s \n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Nem tal�lhat� a k�vetkez� video filter '%s'\n"
#define MSGTR_CouldNotOpenVideoFilter "A k�vetkez� video filter megnyit�sa nem siker�lt: '%s'\n"
#define MSGTR_OpeningVideoFilter "Video filter megnyit�sa: "
#define MSGTR_CannotFindColorspace "Nem tal�lhat� k�z�s colorspace, m�g a 'scale' filterrel sem :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDec: a codec nem �ll�totta be az sh->disp_w �s az sh_disp_h iz�ket, megpr�b�lom workaroundolni!\n"
#define MSGTR_VoConfigRequest "VDec: vo config k�r�s - %d x %d (prefer�lt csp: %s)\n"
#define MSGTR_CouldNotFindColorspace "Nem tal�lok egyez� colorspace-t - �jra pr�b�lom a -vop scale filterrel...\n"
#define MSGTR_MovieAspectIsSet "A film aspect �rt�ke %.2f:1 - aspect ar�ny jav�t�sa.\n"
#define MSGTR_MovieAspectUndefined "A film aspect �rt�ke nem defini�lt - nincs ar�nyjav�t�s.\n"

//  ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "Az MPlayer - r�l"
#define MSGTR_FileSelect "File kiv�laszt�sa ..."
#define MSGTR_SubtitleSelect "Felirat kiv�laszt�sa ..."
#define MSGTR_OtherSelect "File kiv�laszt�sa ..."
#define MSGTR_AudioFileSelect "K�ls� audio csatorna v�laszt�sa ..."
#define MSGTR_FontSelect "Bet�tipus kiv�laszt�sa ..."
#define MSGTR_PlayList "Lej�tsz�si lista"
#define MSGTR_Equalizer "Equalizer"
#define MSGTR_SkinBrowser "Skin b�ng�sz�"
#define MSGTR_Network "Lej�tsz�s WEB - r�l ..."
#define MSGTR_Preferences "Be�ll�t�sok"
#define MSGTR_OSSPreferences "OSS meghajt� be�ll�t�sok"
#define MSGTR_SDLPreferences "SDL meghajt� be�ll�t�sok"
#define MSGTR_NoMediaOpened "nincs megnyitva semmi"
#define MSGTR_VCDTrack "%d. VCD track"
#define MSGTR_NoChapter "nincs megnyitott fejezet"
#define MSGTR_Chapter "%d. fejezet"
#define MSGTR_NoFileLoaded "nincs file bet�ltve"

// --- buttons ---
#define MSGTR_Ok "Ok"
#define MSGTR_Cancel "M�gse"
#define MSGTR_Add "Hozz�ad"
#define MSGTR_Remove "Kivesz"
#define MSGTR_Clear "T�rl�s"
#define MSGTR_Config "Be�ll�t�s"
#define MSGTR_ConfigDriver "Driver be�ll�t�sa"
#define MSGTR_Browse "Tall�z�s"

// --- error messages ---
#define MSGTR_NEMDB "Nincs el�g mem�ria a buffer kirajzol�s�hoz."
#define MSGTR_NEMFMR "Nincs el�g mem�ria a men� renderel�s�hez."
#define MSGTR_IDFGCVD "Nem talaltam gui kompatibilis video meghajt�t."
#define MSGTR_NEEDLAVCFAME "Nem MPEG file lej�tsz�sa nem lehets�ges a DXR3/H+ hardverrel �jrak�dol�s n�lk�l.\nKapcsold be a lavc vagy fame opci�t a DXR3/H+ konfigur�ci�s panelen."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[skin] hiba a skin konfigur�ci�s file-j�nak %d. sor�ban: %s"
#define MSGTR_SKIN_WARNING1 "[skin] figyelmeztet�s a skin konfigur�ci�s file-j�nak %d. sor�ban: widget megvan, de nincs el�tte \"section\" ( %s )"
#define MSGTR_SKIN_WARNING2 "[skin] figyelmeztet�s a skin konfigur�ci�s file-j�nak %d. sor�ban: widget megvan, de nincs el�tte \"subsection\" ( %s )"
#define MSGTR_SKIN_WARNING3 "[skin] figyelmeztet�s a skin konfigur�ci�s file-j�nak %d. sor�ban: ez az elem nem haszn�lhat� ebben az alr�szben ( %s )"
#define MSGTR_SKIN_BITMAP_16bit  "16 vagy kevesebb bites bitmap nem t�mogatott ( %s ).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "file nem tal�lhat� ( %s )\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "bmp olvas�si hiba ( %s )\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "tga olvas�si hiba ( %s )\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "png olvas�si hiba ( %s )\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE t�m�r�tett tga-k nincsenek t�mogatva ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "ismeretlen tipus� file ( %s )\n"
#define MSGTR_SKIN_BITMAP_ConvertError "hiba a 24-r�l 32bitre konvert�l�s k�zben ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "ismeretlen �zenet: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "nincs el�g mem�ria\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "t�l sok bet�tipus van deklar�lva\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "nem tal�lom a bet�tipus file-t\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "nem tal�lom a bet�tipus k�pfile-t"
#define MSGTR_SKIN_FONT_NonExistentFontID "neml�tez� bet�tipus azonos�t� ( %s )\n"
#define MSGTR_SKIN_UnknownParameter "ismeretlen param�ter ( %s )\n"
#define MSGTR_SKINBROWSER_NotEnoughMemory "[skinb�ng�sz�] nincs el�g mem�ria.\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "Skin nem tal�lhat� ( %s ).\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "Skin configfile olvas�si hiba ( %s ).\n"
#define MSGTR_SKIN_LABEL "Skin-ek:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "Az MPlayer-r�l"
#define MSGTR_MENU_Open "Megnyit�s ..."
#define MSGTR_MENU_PlayFile "File lej�tsz�s ..."
#define MSGTR_MENU_PlayVCD "VCD lej�tsz�s ..."  
#define MSGTR_MENU_PlayDVD "DVD lej�tsz�s ..."  
#define MSGTR_MENU_PlayURL "URL lej�tsz�s ..."  
#define MSGTR_MENU_LoadSubtitle "Felirat bet�lt�se ..."
#define MSGTR_MENU_DropSubtitle "Felirat eldob�sa ..."
#define MSGTR_MENU_LoadExternAudioFile "K�ls� hang bet�lt�se ..."
#define MSGTR_MENU_Playing "Lej�tsz�s"
#define MSGTR_MENU_Play "Lej�tsz�s"
#define MSGTR_MENU_Pause "Pillanat�llj"
#define MSGTR_MENU_Stop "�llj"  
#define MSGTR_MENU_NextStream "K�vetkez� file"
#define MSGTR_MENU_PrevStream "El�z� file"
#define MSGTR_MENU_Size "M�ret"
#define MSGTR_MENU_NormalSize "Norm�l m�ret"
#define MSGTR_MENU_DoubleSize "Dupla m�ret"
#define MSGTR_MENU_FullScreen "Teljesk�perny�" 
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "Lemez megnyit�sa ..."
#define MSGTR_MENU_ShowDVDMenu "DVD men�"
#define MSGTR_MENU_Titles "S�vok"
#define MSGTR_MENU_Title "%2d. s�v"
#define MSGTR_MENU_None "(nincs)"
#define MSGTR_MENU_Chapters "Fejezetek"
#define MSGTR_MENU_Chapter "%2d. fejezet"
#define MSGTR_MENU_AudioLanguages "Szinkron nyelvei"
#define MSGTR_MENU_SubtitleLanguages "Feliratok nyelvei"
#define MSGTR_MENU_PlayList "Lej�tsz�si lista"
#define MSGTR_MENU_SkinBrowser "Skin b�ng�sz�"
#define MSGTR_MENU_Preferences "Be�ll�t�sok" 
#define MSGTR_MENU_Exit "Kil�p�s ..."
#define MSGTR_MENU_Mute "N�ma"
#define MSGTR_MENU_Original "Eredeti"
#define MSGTR_MENU_AspectRatio "K�par�ny"
#define MSGTR_MENU_AudioTrack "Audio track"
#define MSGTR_MENU_Track "%d. s�v"
#define MSGTR_MENU_VideoTrack "Video track"

// --- equalizer
#define MSGTR_EQU_Audio "Audio"
#define MSGTR_EQU_Video "Video"
#define MSGTR_EQU_Contrast "Kontraszt: "
#define MSGTR_EQU_Brightness "F�nyer�: "
#define MSGTR_EQU_Hue "Szin�rnyalat: "
#define MSGTR_EQU_Saturation "Tel�tetts�g: "
#define MSGTR_EQU_Front_Left "Bal Els�"
#define MSGTR_EQU_Front_Right "Jobb Els�"
#define MSGTR_EQU_Back_Left "Bal H�ts�"
#define MSGTR_EQU_Back_Right "Jobb H�ts�"
#define MSGTR_EQU_Center "K�z�ps�"
#define MSGTR_EQU_Bass "Basszus"
#define MSGTR_EQU_All "Mindegyik"
#define MSGTR_EQU_Channel1 "1. Csatorna"
#define MSGTR_EQU_Channel2 "2. Csatorna"
#define MSGTR_EQU_Channel3 "3. Csatorna"
#define MSGTR_EQU_Channel4 "4. Csatorna"
#define MSGTR_EQU_Channel5 "5. Csatorna"
#define MSGTR_EQU_Channel6 "6. Csatorna"

// --- playlist
#define MSGTR_PLAYLIST_Path "Utvonal"
#define MSGTR_PLAYLIST_Selected "Kiv�lasztott file - ok"
#define MSGTR_PLAYLIST_Files "File - ok"
#define MSGTR_PLAYLIST_DirectoryTree "K�nyvt�r lista"

// --- preferences
#define MSGTR_PREFERENCES_Audio "Audio"
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_SubtitleOSD "Felirat & OSD"
#define MSGTR_PREFERENCES_Codecs "Kodekek �s demuxerek"
#define MSGTR_PREFERENCES_Misc "Egy�b"

#define MSGTR_PREFERENCES_None "Egyik sem"
#define MSGTR_PREFERENCES_AvailableDrivers "Driverek:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Hang n�lk�l"
#define MSGTR_PREFERENCES_NormalizeSound "Hang normaliz�l�sa"
#define MSGTR_PREFERENCES_EnEqualizer "Audio equalizer"
#define MSGTR_PREFERENCES_ExtraStereo "Extra stereo"
#define MSGTR_PREFERENCES_Coefficient "Egy�tthat�:"
#define MSGTR_PREFERENCES_AudioDelay "Hang k�sleltet�s"
#define MSGTR_PREFERENCES_DoubleBuffer "Dupla bufferel�s"
#define MSGTR_PREFERENCES_DirectRender "Direct rendering"
#define MSGTR_PREFERENCES_FrameDrop "K�p eldob�s"
#define MSGTR_PREFERENCES_HFrameDrop "Er�szakos k�p eldob�"
#define MSGTR_PREFERENCES_Flip "K�p fejjel lefel�"
#define MSGTR_PREFERENCES_Panscan "Panscan: "
#define MSGTR_PREFERENCES_OSDTimer "�ra es indik�torok"
#define MSGTR_PREFERENCES_OSDProgress "Csak a sz�zal�k jelz�k"
#define MSGTR_PREFERENCES_OSDTimerPercentageTotalTime "�ra, sz�zal�k �s a teljes id�"
#define MSGTR_PREFERENCES_Subtitle "Felirat:"
#define MSGTR_PREFERENCES_SUB_Delay "K�sleltet�s: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Poz�ci�ja: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Felirat automatikus bet�lt�s�nek tilt�sa"
#define MSGTR_PREFERENCES_SUB_Unicode "Unicode felirat"
#define MSGTR_PREFERENCES_SUB_MPSUB "A film felirat�nak konvert�l�sa MPlayer felirat form�tumba"
#define MSGTR_PREFERENCES_SUB_SRT "A film felirat�nak konvert�l�sa SubViewer ( SRT ) form�tumba"
#define MSGTR_PREFERENCES_SUB_Overlap "Felirat �tlapol�s"
#define MSGTR_PREFERENCES_Font "Bet�k:"
#define MSGTR_PREFERENCES_FontFactor "Bet� egy�tthat�:"
#define MSGTR_PREFERENCES_PostProcess "K�pjav�t�s"
#define MSGTR_PREFERENCES_AutoQuality "Aut�matikus min�s�g �ll�t�s: "
#define MSGTR_PREFERENCES_NI "non-interleaved  AVI  felt�telez�se (hib�s AVI-kn�l seg�thet"
#define MSGTR_PREFERENCES_IDX "Az AVI index�nek �jra�p�t�se, ha sz�ks�ges"
#define MSGTR_PREFERENCES_VideoCodecFamily "Video kodek csal�d:"
#define MSGTR_PREFERENCES_AudioCodecFamily "Audio kodek csal�d:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "OSD szint"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Felirat"
#define MSGTR_PREFERENCES_FRAME_Font "Bet�"
#define MSGTR_PREFERENCES_FRAME_PostProcess "K�pjav�t�s"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Codec & demuxer"
#define MSGTR_PREFERENCES_FRAME_Cache "Gyors�t�t�r"
#define MSGTR_PREFERENCES_FRAME_Misc "Egy�b"
#define MSGTR_PREFERENCES_OSS_Device "Meghajt�:"
#define MSGTR_PREFERENCES_OSS_Mixer "Mixer:"
#define MSGTR_PREFERENCES_SDL_Driver "Meghajt�:"
#define MSGTR_PREFERENCES_Message "K�rlek eml�kezz, n�h�ny opci� ig�nyli a lej�tsz�s �jraind�t�s�t."
#define MSGTR_PREFERENCES_DXR3_VENC "Video k�dol�:"
#define MSGTR_PREFERENCES_DXR3_LAVC "LAVC haszn�lata (ffmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "FAME haszn�lata"
#define MSGTR_PREFERENCES_FontEncoding1 "Unicode"
#define MSGTR_PREFERENCES_FontEncoding2 "Nyugat-Eur�pai karakterk�szlet (ISO-8859-1)"
#define MSGTR_PREFERENCES_FontEncoding3 "Nyugat-Eur�pai karakterk�szlet eur�val (ISO-8859-15)"
#define MSGTR_PREFERENCES_FontEncoding4 "Szl�v / K�z�p-Eur�pai karakterk�szlet (ISO-8859-2)"
#define MSGTR_PREFERENCES_FontEncoding5 "Eszperant�, gall, m�ltai, t�r�k karakterk�szlet (ISO-8859-3)"
#define MSGTR_PREFERENCES_FontEncoding6 "R�gi baltik karakterk�szlet (ISO-8859-4)"
#define MSGTR_PREFERENCES_FontEncoding7 "Cirill karakterk�szlet (ISO-8859-5)"
#define MSGTR_PREFERENCES_FontEncoding8 "Arab karakterk�szlet (ISO-8859-6)"
#define MSGTR_PREFERENCES_FontEncoding9 "Modern g�r�g karakterk�szlet (ISO-8859-7)"
#define MSGTR_PREFERENCES_FontEncoding10 "T�r�k karakterk�szlet (ISO-8859-9)"
#define MSGTR_PREFERENCES_FontEncoding11 "Baltik karakterk�szlet (ISO-8859-13"
#define MSGTR_PREFERENCES_FontEncoding12 "Kelta karakterk�szlet (ISO-8859-14)"
#define MSGTR_PREFERENCES_FontEncoding13 "H�ber karakterk�szlet (ISO-8859-8)"
#define MSGTR_PREFERENCES_FontEncoding14 "Orosz karakterk�szlet (KOI8-R)"
#define MSGTR_PREFERENCES_FontEncoding15 "Ukr�n, Belorusz karakterk�szlet (KOI8-U/UR)"
#define MSGTR_PREFERENCES_FontEncoding16 "Egyszer� k�nai karakterk�szlet (CP936)"
#define MSGTR_PREFERENCES_FontEncoding17 "Tradicion�lis k�nai karakterk�szlet (BIG5)"
#define MSGTR_PREFERENCES_FontEncoding18 "Jap�n karakterk�szlet (SHIFT-JIS)"
#define MSGTR_PREFERENCES_FontEncoding19 "Koreai karakterk�szlet (CP949)"
#define MSGTR_PREFERENCES_FontEncoding20 "Thai karakterk�szlet (CP874)"
#define MSGTR_PREFERENCES_FontEncoding21 "Cirill Winny�z (CP1251)"
#define MSGTR_PREFERENCES_FontNoAutoScale "Nincs automata karakterm�ret v�laszt�s"
#define MSGTR_PREFERENCES_FontPropWidth "Karakterm�ret film sz�less�g�hez val� �ll�t�sa"
#define MSGTR_PREFERENCES_FontPropHeight "Karakterm�ret film magass�g�hoz val� �ll�t�sa"
#define MSGTR_PREFERENCES_FontPropDiagonal "Karakterm�ret film �tl�j�hoz val� �ll�t�sa"
#define MSGTR_PREFERENCES_FontEncoding "K�dol�s:"
#define MSGTR_PREFERENCES_FontBlur "Blur:"
#define MSGTR_PREFERENCES_FontOutLine "K�rvonal:"
#define MSGTR_PREFERENCES_FontTextScale "Sz�veg sk�la:"
#define MSGTR_PREFERENCES_FontOSDScale "OSD sk�la:"
#define MSGTR_PREFERENCES_Cache "Gyors�t�t�r be/ki"
#define MSGTR_PREFERENCES_CacheSize "Gyors�t�t�r merete:"
#define MSGTR_PREFERENCES_LoadFullscreen "Ind�t�s teljes k�perny�n"
#define MSGTR_PREFERENCES_SaveWinPos "Ablakok poz�ci�j�nak ment�se"
#define MSGTR_PREFERENCES_XSCREENSAVER "XScreenSaver le�ll�t�sa film lej�tsz�sakor"
#define MSGTR_PREFERENCES_PlayBar "PlayBar enged�lyez�se"
#define MSGTR_PREFERENCES_AutoSync "AutoSync ki/be kapcsol�sa"
#define MSGTR_PREFERENCES_AutoSyncValue "�rt�ke:"
#define MSGTR_PREFERENCES_CDROMDevice "CD meghajt�:"
#define MSGTR_PREFERENCES_DVDDevice "DVD meghajt�:"
#define MSGTR_PREFERENCES_FPS "Film FPS:"
#define MSGTR_PREFERENCES_ShowVideoWindow "Lej�tsz� ablak megjelen�t�se ha inakt�v"

#define MSGTR_ABOUT_UHU "GUI fejleszt�st az UHU Linux t�mogatta\n"
#define MSGTR_ABOUT_CoreTeam "   MPlayer csapat:\n"
#define MSGTR_ABOUT_AdditionalCoders "   Tov�bbi k�derek:\n"
#define MSGTR_ABOUT_MainTesters "   Teszterek:\n"

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "V�gzetes hiba!"
#define MSGTR_MSGBOX_LABEL_Error "Hiba!"
#define MSGTR_MSGBOX_LABEL_Warning "Figyelmeztet�s!"

#endif
