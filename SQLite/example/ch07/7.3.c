void str_agg_step(sqlite3_context* ctx, int ncols, sqlite3_value** values)
{
  SAggCtx *p = (SAggCtx *) sqlite3_aggregate_context(ctx, sizeof(*p));

  static const char delim [] = “, “;

  char *txt = sqlite3_value_text(values[0]);

  int len = strlen(txt);

  if (!p->result) {
    p->result = sqlite_malloc(len + 1);
    memcpy(p->result, txt, len + 1);
    p->chrCnt = len;
  }
  else
  {
    const int delimLen = sizeof(delim);
    p->result = sqlite_realloc(p->result, p->chrCnt + len + delimLen + 1);
    memcpy(p->result +  p->chrCnt, delim, delimLen);
    p->chrCnt += delimLen;
    memcpy(p->result +  p->chrCnt, txt, len + 1);
    p->chrCnt += len;
  }
}
