void str_agg_finalize(sqlite3_context* ctx)
{
  SAggCtx *p = (SAggCtx *) sqlite3_aggregate_context(ctx, sizeof(*p));
  if( p && p->result ) sqlite3_result_text(ctx, p->result, p->chrCnt, sqlite_free);
}
