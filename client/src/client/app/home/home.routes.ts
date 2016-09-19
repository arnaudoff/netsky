import { Route } from '@angular/router';
import { HomeComponent } from './index';

import { InterfaceStepRoutes } from './interface-step/index';
import { FilterStepRoutes } from './filter-step/index';
import { SharingStepRoutes } from './sharing-step/index';
import { StartStepRoutes } from './start-step/index';

export const HomeRoutes: Route[] = [
  {
    path: 'home',
    component: HomeComponent,
    children: [
      ...InterfaceStepRoutes,
      ...FilterStepRoutes,
      ...SharingStepRoutes,
      ...StartStepRoutes,
    ]
  }
];
