import { Route } from '@angular/router';
import { InterfaceStepComponent } from './index';

export const InterfaceStepRoutes: Route[] = [
  {
    path: '',
    redirectTo: 'interface'
  },
  {
    path: 'interface',
    component: InterfaceStepComponent
  }
];
