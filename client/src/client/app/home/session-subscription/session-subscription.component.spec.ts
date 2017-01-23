import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { SessionSubscriptionModule } from './session-subscription.module';

export function main() {
   describe('Session subscription component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [SessionSubscriptionModule]
      });
    });

    it('should have text describing that there is an existing session',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let subscriptionDOMElement =
              fixture.debugElement.children[0].nativeElement;

            expect(
              subscriptionDOMElement
                .querySelectorAll('.content')[0].textContent)
                .toEqual('There is a session available right now');
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<session-subscription></session-subscription>'
})

class TestComponent {}
