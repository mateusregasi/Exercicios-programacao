import "package:flutter/material.dart";
import "interface.dart";

void main(){
  runApp(
    MaterialApp(
      title: "Pokedex",
      debugShowCheckedModeBanner: false,
      home: Interface(),
    )
  );
}