/*==========================================
 * 	MOB Alive
 *------------------------------------------*/
ACMD_FUNC(mobalive)
{
	char mob_name[100];
	int mob_id;
	int number = 0;
	struct s_mapiterator* it;

	nullpo_retr(-1, sd);

	if (!message || !*message || sscanf(message, "%99[^\n]", mob_name) < 1) {
		clif_displaymessage(fd, "Por favor, digite o nome do monstro (uso: @mobalive <nome>).");
		return -1;
	}

	if ((mob_id = atoi(mob_name)) == 0)
		 mob_id = mobdb_searchname(mob_name);
	if(mob_id > 0 && mobdb_checkid(mob_id) == 0){
		snprintf(atcmd_output, sizeof atcmd_output, "ID %s inválido!",mob_name);
		clif_displaymessage(fd, atcmd_output);
		return -1;
	}
	if(mob_id == atoi(mob_name) && mob_db(mob_id)->jname)
				strcpy(mob_name,mob_db(mob_id)->jname);	// --ja--
//				strcpy(mob_name,mob_db(mob_id)->name);	// --en--

	snprintf(atcmd_output, sizeof atcmd_output, "Procurando pelo monstro %s em %s ...", mob_name, mapindex_id2name(sd->mapindex));
	clif_displaymessage(fd, atcmd_output);

	it = mapit_geteachmob();
	while( ! number )
	{
		TBL_MOB* md = (TBL_MOB*)mapit_next(it);
		if( md == NULL )
			break;// no more mobs

		if( md->bl.m != sd->bl.m )
			continue;
		if( mob_id != -1 && md->class_ != mob_id )
			continue;

		if( md->spawn_timer == INVALID_TIMER )
		{
			++ number;
			snprintf(atcmd_output, sizeof(atcmd_output), "Há pelo menos um %s vivo.", md->name);
			clif_displaymessage(fd, atcmd_output);
		}
	}
	if ( ! number )
		clif_displaymessage(fd, "Nenhum encontrado.");
	mapit_free(it);

	return 0;
}


/*==========================================
 * 	MOB Alive2
 *------------------------------------------*/
int atcommand_mobalive2(const int fd, struct map_session_data* sd, const char* command, const char* message)
{
	char mob_name[100];
	int mob_id;
	int number = 0;
	struct s_mapiterator* it;

	nullpo_retr(-1, sd);

	if (!message || !*message || sscanf(message, "%99[^\n]", mob_name) < 1) {
		clif_displaymessage(fd, "Por favor, digite o nome do monstro (uso: @mobalive <nome>).");
		return -1;
	}

	if ((mob_id = atoi(mob_name)) == 0)
		 mob_id = mobdb_searchname(mob_name);
	if(mob_id > 0 && mobdb_checkid(mob_id) == 0){
		snprintf(atcmd_output, sizeof atcmd_output, "ID %s inválido!",mob_name);
		clif_displaymessage(fd, atcmd_output);
		return -1;
	}
	if(mob_id == atoi(mob_name) && mob_db(mob_id)->jname)
				strcpy(mob_name,mob_db(mob_id)->jname);	// --ja--
//				strcpy(mob_name,mob_db(mob_id)->name);	// --en--

	snprintf(atcmd_output, sizeof atcmd_output, "Procurando pelo monstro %s em %s ...", mob_name, mapindex_id2name(sd->mapindex));
	clif_displaymessage(fd, atcmd_output);

	it = mapit_geteachmob();
	while( true )
	{
		TBL_MOB* md = (TBL_MOB*)mapit_next(it);
		if( md == NULL )
			break;// no more mobs

		if( md->bl.m != sd->bl.m )
			continue;
		if( mob_id != -1 && md->class_ != mob_id )
			continue;

		if( md->spawn_timer == INVALID_TIMER )
			++ number;
	}
	snprintf(atcmd_output, sizeof(atcmd_output), "%s (%d %s)", md->name, number, (number == 1) ? "vivo" : "vivos");
	clif_displaymessage(fd, atcmd_output);
	mapit_free(it);

	return 0;
}