package com.example.android.apis;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.*;
import android.database.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.io.*;

public class MyDatabaseHelper {
  private static final String DBNAME = "foods.db";
  private static final String DBPATH = "/data/data/com.example.android.apis/databases/";
  private static final String TABLE_NAME = "foods";
  private Context myContext;
  private SQLiteDatabase myDatabase;
  private SQLiteStatement myInsertStatement;
  private static final String FOODINSERT = "insert into " + TABLE_NAME + "(type_id, name) values (?, ?)";

//constructor  
public MyDatabaseHelper(Context context) {
  this.myContext = context;
  OpenHelper openHelper = new OpenHelper(this.myContext);
  try {
  	  this.createDatabase();
  }
  catch (IOException e) {
  	  //throw new Error("Failed to create Seinfeld database");
  }
  this.myDatabase = openHelper.getWritableDatabase();
  this.myInsertStatement = this.myDatabase.compileStatement(FOODINSERT);
}

//Insert method for recreating foods table if needed.
public long insert(Integer type_id, String name) {
  this.myInsertStatement.bindLong(1, type_id);
  this.myInsertStatement.bindString(2, name);
  return this.myInsertStatement.executeInsert();
}

//Delete method for deleting all rows
public void deleteFoods() {
  this.myDatabase.delete(TABLE_NAME, null, null);
}


public List<String> selectFoods() {
  List<String> list = new ArrayList<String>();
  Cursor cursor = this.myDatabase.query(TABLE_NAME, new String[] { "name" }, null, null, null, null, null);
  if (cursor.moveToFirst()) {
    do {
      list.add(cursor.getString(0));
    } while (cursor.moveToNext());
  }
  if (cursor != null && !cursor.isClosed()) {
    cursor.close();
  }
  return list;
}

//create an empty db, and replace with our chosen db
public void createDatabase() throws IOException{
  if (!checkDatabase()) {
    OpenHelper openHelper = new OpenHelper(this.myContext);
    this.myDatabase = openHelper.getWritableDatabase();
    try {
      copyDatabase();
    }
    catch (IOException e) {
	  throw new Error("Error copying database from system assets");
    }
  }
}

//Check if our database already exists
private boolean checkDatabase(){
  SQLiteDatabase checkableDatabase = null;
  try {
    checkableDatabase = 
      SQLiteDatabase.openDatabase(DBPATH+DBNAME, null,
                                  SQLiteDatabase.OPEN_READONLY);
  }
  catch (SQLiteException e) {
    //our database doesn't exist, so we'll return false below.
  }
  if (checkableDatabase != null) {
    checkableDatabase.close();
  }
  return checkableDatabase != null ? true : false;
}

//Copy our database from the Application's assets
//over the empty DB for use
private void copyDatabase() throws IOException{

  InputStream myInput = myContext.getAssets().open(DBNAME);
  OutputStream myOutput = new FileOutputStream(DBPATH+DBNAME);

  byte[] buffer = new byte[1024];
  int length;
  while ((length = myInput.read(buffer))>0){
    myOutput.write(buffer, 0, length);
  }

  myOutput.flush();
  myOutput.close();
  myInput.close();
}

public void openDatabase() throws SQLException{
  myDatabase = SQLiteDatabase.openDatabase(DBPATH+DBNAME, null,
                                           SQLiteDatabase.OPEN_READWRITE);
}

private static class OpenHelper extends SQLiteOpenHelper {
  OpenHelper(Context context) {
  super(context, DBNAME, null, 1);
}
  
@Override
public void onCreate(SQLiteDatabase db) {
  // if something goes wrong using foods.db asset, revert to creating a simplified version for demo
  //db.execSQL("create table " + TABLE_NAME + "(id integer primary key, type_id integer, name text)");
}

@Override
public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
  db.execSQL("drop table if exists " + TABLE_NAME);
  onCreate(db);
}
}
}
