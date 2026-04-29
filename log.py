import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('deriv_errors.csv')
h = df['h']
err_fwd = df['forward_error']
err_bwd = df['backward_error']
err_cen = df['central_error']
err_rom = df['romberg_error']

plt.figure(figsize=(10, 6))
plt.loglog(h, err_fwd, 'o-', label='Вперёд (O(h))')
plt.loglog(h, err_bwd, 's-', label='Назад (O(h))')
plt.loglog(h, err_cen, '^-', label='Центральная (O(h²))')
plt.loglog(h, err_rom, 'd-', label='Рунге-Ромберга (O(h⁴))')
plt.xlabel('Шаг h')
plt.ylabel('Абсолютная погрешность')
plt.title('Сравнение точности методов численного дифференцирования')
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('deriv_comparison.png', dpi=150)
plt.show()