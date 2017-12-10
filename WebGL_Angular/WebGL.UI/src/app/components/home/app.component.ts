import { Component } from '@angular/core';
// import * as THREE from 'three';
// // import { OrbitControls } from 'three-orbit-controls';
// import { OrbitControls } from 'three-orbitcontrols-ts';
// // import { MeshPhongMaterial, WebGLRenderer, PerspectiveCamera } from 'three';
// // import { OrbitControls, Scene } from 'three';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  // @ViewChild('rendererContainer') rendererContainer: ElementRef;

  // renderer = new THREE.WebGLRenderer();
  // scene = null;
  // camera = null;
  // materials = null;
  // controls = null;


  // cylinder = {
  //   bottomCtr:{
  //     X:0.0,
  //     Y:0.0,
  //     Z:0.0},
  //   topCtr:{
  //     X:0.0,
  //     Y:0.0,
  //     Z:200.0},
  //   baseRadius:100
  // };

  // testpt = {X:200, Y:100, Z:500};

  // cylinderGLobj = null;
  // sphereGLobj = null;


  // constructor() {
  //   this.scene = new THREE.Scene();

  //   //camera
  //   this.camera = new THREE.PerspectiveCamera(75, 600 / 400, 1, 10000);
  //   this.camera.position.z = 1000;

  //   // controls
  //   this.controls = new OrbitControls(this.camera, this.renderer.domElement);
  //   this.controls.addEventListener( 'change', this.renderScene );

  //   // light
  //   var light = new THREE.DirectionalLight( 0xffffff );
  //   light.position.set( 0, 1, 1 ).normalize();
  //   this.scene.add(light);

  //   // ambient light
  //   var ambient = new THREE.AmbientLight ( 0x555555 );
  //   this.scene.add(ambient);

  //   // axes
  //   var axis = new THREE.AxisHelper( 600 ) 
  //   axis.position.set( 0,0,0 );
  //   //axis.rotation.x = Math.PI/4;
  //   this.scene.add(axis);

  //   // grid (floor)
  //   var gridXY = new THREE.GridHelper(800, 10);
  //   gridXY.position.set( 0,0,0 );
  //   gridXY.rotation.x = Math.PI/2;
  //   gridXY.setColors( new THREE.Color(0x000066), new THREE.Color(0x000066) );
  //   this.scene.add(gridXY);

  //   var dx = this.cylinder.topCtr.X-this.cylinder.bottomCtr.X;
  //   var dy = this.cylinder.topCtr.Y-this.cylinder.bottomCtr.Y;
  //   var dz = this.cylinder.topCtr.Z-this.cylinder.bottomCtr.Z;
  //   var cylHeight = Math.sqrt(dx*dx+dy*dy+dz*dz);
  //   var cylRadius = this.cylinder.baseRadius;
  //   var cylindergeometry = new THREE.CylinderGeometry(cylRadius,cylRadius,cylHeight,16,16,false);
  //   var cylinderMaterial = new THREE.MeshLambertMaterial( {color: 0x000088} );
  //   this.cylinderGLobj = new THREE.Mesh(cylindergeometry, cylinderMaterial);
  //   this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z);
  //   this.cylinderGLobj.rotation.x = Math.PI/2;
  //   this.scene.add(this.cylinderGLobj);
    
    
  //   // Sphere parameters: radius, segments along width, segments along height 
  //   var spheregeometry = new THREE.SphereGeometry( 15, 32, 16 ); 
  //   var sphereMaterial = new THREE.MeshLambertMaterial( {color: 0x8888ff} ); 
  //   this.sphereGLobj = new THREE.Mesh(spheregeometry, sphereMaterial);
  //   this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
  //   this.scene.add(this.sphereGLobj);
  // }


  // ngAfterViewInit() {
  //     this.renderer.setSize(600, 400);
  //     this.renderer.domElement.style.display = "block";
  //     this.renderer.domElement.style.margin = "auto";
  //     this.rendererContainer.nativeElement.appendChild(this.renderer.domElement);

  //     this.animate();
  // }

  // animate() {
  //   window.requestAnimationFrame(() => this.animate());

  //   this.updateScene();

  //   this.renderScene();
  // }

  // renderScene(){
  //   this.renderer.render(this.scene, this.camera);
  // }

  // updateScene(){
  //   this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z)

  //   this.cylinderGLobj.baseRadius = this.cylinder.baseRadius;

  //   this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
  // }
}
