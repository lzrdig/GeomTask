import { ModuleWithProviders }  from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { Dashboard } from './components/dashboard/dashboard.component'
import { PersonalCabinet } from './components/personalCabinet/personalCabinet.component'
import { WebGlComponent } from './components/webglscreen/webglscreen.component'

const appRoutes: Routes = [
    {
        path: '',
        component: Dashboard
    },
    {
        path: 'personal',
        component: PersonalCabinet
    },
    {
        path: 'webgl',
        component: WebGlComponent
    },
    {
        path: '**',  // otherwise route.
        component: Dashboard
    }
];


export const routing: ModuleWithProviders = RouterModule.forRoot(appRoutes);