import { Routes } from '@angular/router';

import { StartComponent } from './components/start/start.component';
import { WebglwndComponent } from './components/webglwnd/webglwnd.component';


export const routerConfig: Routes = [
    {   path: 'start',   component: StartComponent    },    
    {   path: 'webgl',   component: WebglwndComponent    },
    {   path: '',  redirectTo: '/start',   pathMatch: 'full'    },
    {   path: '**',  redirectTo: '/start',  pathMatch: 'full'    }
];