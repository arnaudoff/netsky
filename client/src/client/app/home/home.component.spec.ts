import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { HomeComponent } from './home.module';

export function main() {
   describe('Home component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [HomeModule]
      });
    });

    it('should have text describing that interface should be chosen',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let homeDOMElement = fixture.debugElement.children[0].nativeElement;

	          expect(homeDOMElement.querySelectorAll('p')[0].textContent).toEqual('Choose an interface to sniff');
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<home></home>'
})

class TestComponent {}
