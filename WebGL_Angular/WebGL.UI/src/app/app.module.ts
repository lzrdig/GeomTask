import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { RouterModule } from '@angular/router';

import * as THREE from 'three';

import { AppComponent } from './components/home/app.component';
import { WebglwndComponent } from './components/webglwnd/webglwnd.component';
import { TopnavComponent } from './components/topnav/topnav.component';

import { routerConfig } from './app.routing';
import { StartComponent } from './components/start/start.component';

@NgModule({
  declarations: [
    AppComponent,
    WebglwndComponent,
    TopnavComponent,
    StartComponent,
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule,
    RouterModule.forRoot(routerConfig)
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
