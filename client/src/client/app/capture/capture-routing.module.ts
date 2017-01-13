import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';
import { CaptureComponent } from './capture.component';

@NgModule({
  imports: [
    RouterModule.forChild([
      { path: 'capture', component: CaptureComponent }
    ])
  ],
  exports: [RouterModule]
})
export class CaptureRoutingModule { }
