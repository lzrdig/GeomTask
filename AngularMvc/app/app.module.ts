import { NgModule }      from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';

import { AppComponent }   from './components/app/app.component';
import { Dashboard } from './components/dashboard/dashboard.component'
import { PersonalCabinet } from './components/personalCabinet/personalCabinet.component'
import { NavComponent } from './components/topnav/topnav.component'
import { WebGlComponent } from './components/webglscreen/webglscreen.component'

import { routing } from './app.routing';

@NgModule({
    imports: [BrowserModule,FormsModule, routing],
    declarations: [AppComponent, Dashboard, PersonalCabinet, WebGlComponent, NavComponent],
    bootstrap: [AppComponent]
})

export class AppModule {}