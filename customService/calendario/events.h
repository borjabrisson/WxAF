#ifndef CalendarioEvents_H_
#define CalendarioEvents_H_

enum ACT_Calendar {
	ACT_newNote = 321,
	ACT_editNote,
	ACT_delNote,
	ACT_addComment,
	ACT_editComment,
	ACT_delComment
};

enum typeList_Calendar {
	type_noteList = 341, type_dataList
};

enum Qry_Calendar {
	query_note = 351, query_dataset
};

#endif /* CalendarioEvents_H_ */
