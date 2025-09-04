import "package:flutter/material.dart";

void main(){
  runApp(
    MaterialApp(
      title:"Interface App",
      debugShowCheckedModeBanner: false,
      home: Container(
        decoration: BoxDecoration(
          color: Colors.white70,
        ),
        child: Center(child:Text("Oi")),
      ),
    )
  );
}
